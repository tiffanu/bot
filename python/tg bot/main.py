import openai
import telebot
import json

file = open('config.json', 'r')
config = json.load(file)

TOKEN = config['token']
openai.api_key = config['openai']

bot = telebot.TeleBot(TOKEN)

@bot.message_handler(commands=['start'])
def welcome(message):
    bot.reply_to(message, 'Привет! Напиши /help, чтобы начать диалог')


@bot.message_handler(commands=['help'])
def help(message):
    bot.reply_to(message, 'Чтобы задать вопрос, напиши /ask')


@bot.message_handler(commands=['ask'])
def question(message):
    try:
        bot.reply_to(message, 'Какой вопрос ты хотел задать?')

        def handler_question(response):
            try:

                result = openai.Completion.create(
                    model="text-davinci-003",
                    prompt=response.text,
                    temperature=0.9,
                    max_tokens=3000,
                    top_p=1,
                    frequency_penalty=0.0,
                    presence_penalty=0.6,
                    stop=[" Human:", " AI:"]
                )

                bot.reply_to(message, result['choices'][0]['text'])
                bot.reply_to(message, 'Чтобы задать другой вопрос, напиши команду /ask ещё раз')

            except Exception as ex:
                bot.reply_to(message, 'Я тебя не понимаю. Попробуй ещё раз')

        bot.register_next_step_handler(message, handler_question)

    except Exception as ex:
        bot.reply_to(message, 'Я тебя не понимаю. Попробуй ещё раз')


bot.polling()