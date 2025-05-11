import gradio as gr
import nltk
import random
from nltk.chat.util import Chat, reflections
from nltk.tokenize import word_tokenize
from nltk.corpus import wordnet
from nltk.stem import WordNetLemmatizer
from nltk import pos_tag

# Ensure NLTK data is downloaded
nltk.download("punkt")
nltk.download("averaged_perceptron_tagger")
nltk.download("wordnet")

lemmatizer = WordNetLemmatizer()

# Custom reflections
custom_reflections = {
    "i am": "you are", "i was": "you were", "i": "you", "i'm": "you are",
    "i'd": "you would", "i've": "you have", "i'll": "you will", "my": "your",
    "you are": "I am", "you were": "I was", "you've": "I have", "you'll": "I will",
    "your": "my", "yours": "mine", "you": "me", "me": "you"
}

# Patterns
patterns = [
    (r'hi|hello|hey|greetings', ['Hello!', 'Hi there!', 'Greetings!']),
    (r'how are you?', ["I'm doing well, thank you!", "I'm great! How about you?"]),
    (r'(*). your name(.*)', ["I'm ChatBot. Nice to meet you!", "You can call me ChatBot."]),
    (r'what can you do(.*)', [
        "I can chat with you about various topics like technology, science, weather, and more!",
        "I can answer questions, provide information, or just have a friendly conversation."
    ]),
    (r'(.*) (age|old) (.*)', ["I'm just a program, so I don't have an age!", "I was created recently, so I'm quite young!"]),
    (r'(.*) (weather|temperature) (.*)', [
        "I'm not connected to weather services, but I hope it's nice where you are!",
        "You might want to check a weather app for accurate forecasts."
    ]),
    (r'(.*) (science|technology|tech) (.*)', [
        "Science and technology are fascinating! Did you know the first computer programmer was Ada Lovelace in the 1840s?",
        "Technology is advancing rapidly. AI like me is just one example of recent developments."
    ]),
    (r'(.*) (sports|football|basketball|soccer) (.*)', [
        "I'm not much of a sports expert, but I know many people enjoy watching and playing sports!",
        "Sports are great for health and entertainment. Do you have a favorite team?"
    ]),
    (r'(.*) (music|song|band) (.*)', [
        "Music is wonderful! It can affect our moods and emotions.",
        "There are so many genres of music - pop, rock, classical, jazz... What do you like?"
    ]),
    (r'(.*) (movie|film) (.*)', [
        "Movies are a great way to tell stories. Do you prefer action, comedy, or drama?",
        "The first motion picture was made in the late 19th century. How far cinema has come!"
    ]),
    (r'(.*) (book|read|novel) (.*)', [
        "Reading expands the mind. What's the last book you enjoyed?",
        "Books can transport us to different worlds. I'm a fan of classic literature myself."
    ]),
    (r'(.*) (food|eat|cuisine) (.*)', [
        "Food is essential and delicious! Do you like cooking or prefer eating out?",
        "Every culture has its unique cuisine. What's your favorite dish?"
    ]),
    (r'(.*) (travel|vacation|trip) (.*)', [
        "Traveling broadens our horizons. Where was your last vacation?",
        "There are so many beautiful places in the world to visit!"
    ]),
    (r'(.*) (joke|funny) (.*)', [
        "Why don't scientists trust atoms? Because they make up everything!",
        "Why did the scarecrow win an award? Because he was outstanding in his field!"
    ]),
    (r'(.*) (thank you|thanks) (.*)', ["You're welcome!", "No problem!", "Happy to help!"]),
    (r'(.*) (sorry|apologize) (.*)', ["No need to apologize!", "It's alright!", "No worries!"]),
    (r'(.*) (love|like) (.*)', ["That's wonderful to hear!", "Positive emotions are great!"]),
    (r'(.*) (hate|dislike) (.*)', ["I'm sorry to hear that.", "Sometimes we feel that way."]),
    (r'(.*) (help|support) (.*)', ["I'll do my best to help. What do you need?", "How can I assist you?"]),
    (r'(.*) (time|date) (.*)', ["I don't have access to real-time data, but you can check your device's clock!"]),
    (r'(.*)', [
        "I see. Tell me more about that.",
        "Interesting! Can you elaborate?",
        "I understand. What else would you like to discuss?",
        "That's a good point. What's on your mind?"
    ])
]

# Initialize Chat
chatbot = Chat(patterns, custom_reflections)

# Response generation
def generate_response(message, history):
    tokens = word_tokenize(message.lower())
    tagged = pos_tag(tokens)
    nouns = [word for word, pos in tagged if pos.startswith('NN')]
    verbs = [word for word, pos in tagged if pos.startswith('VB')]
    synonyms = set()
    for word in tokens:
        for syn in wordnet.synsets(word):
            for lemma in syn.lemmas():
                synonyms.add(lemma.name())

    response = chatbot.respond(message)

    if response is None or random.random() < 0.3:
        if nouns:
            return f"Tell me more about {random.choice(nouns)}."
        elif verbs:
            return f"What makes you think about {random.choice(verbs)}ing?"
        elif synonyms:
            return f"Ah, {random.choice(list(synonyms))} is related. Can you tell me more?"
        else:
            return random.choice([
                "That's an interesting perspective. Can you elaborate?",
                "I'd love to hear more about your thoughts.",
                "What else would you like to discuss?"
            ])
    return response

# Gradio Interface
demo = gr.ChatInterface(
    fn=generate_response,
    title="🤖 NLTK NLP ChatBot",
    description="Chat with me about books, tech, travel, food, or just say hi!",
    theme="soft"
)

demo.launch()