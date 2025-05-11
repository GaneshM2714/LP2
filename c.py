import nltk
from nltk.chat.util import Chat
from nltk.tokenize import word_tokenize
from nltk import pos_tag
import random
from nltk.stem import WordNetLemmatizer
from nltk.corpus import wordnet
import gradio as gr

# Ensure you have downloaded the necessary NLTK data by uncommenting and running these lines once:
# import nltk
# try:
#     nltk.data.find('tokenizers/punkt')
# except nltk.downloader.DownloadError:
#     nltk.download('punkt')
# try:
#     nltk.data.find('taggers/averaged_perceptron_tagger')
# except nltk.downloader.DownloadError:
#     nltk.download('averaged_perceptron_tagger')
# try:
#     nltk.data.find('corpora/wordnet')
# except nltk.downloader.DownloadError:
#     nltk.download('wordnet')
# try:
#     nltk.data.find('corpora/omw-1.4')
# except nltk.downloader.DownloadError:
#      nltk.download('omw-1.4') # Open Multilingual Wordnet, often needed for wordnet

custom_reflections = {
    "i am": "you are", "i was": "you were", "i": "you", "i'm": "you are",
    "i'd": "you would", "i've": "you have", "i'll": "you will", "my": "your",
    "you are": "I am", "you were": "I was", "you've": "I have", "you'll": "I will",
    "your": "my", "yours": "mine", "you": "me", "me": "you"
}

# Corrected patterns for better matching of keywords
patterns = [
    # Use word boundaries \b or simply remove spaces around keywords for flexibility
    (r'(.*)\b(hi|hello|hey|greetings)\b(.*)', ['Hello!', 'Hi there!', 'Greetings!']),
    (r'(.*)how are you\??(.*)', ["I'm doing well, thank you!", "I'm great! How about you?"]),
    (r'(.*) your name(.*)', ["I'm ChatBot. Nice to meet you!", "You can call me ChatBot."]),
    (r'(.*)what can you do\??(.*)', [
        "I can chat with you about various topics like technology, science, weather, and more!",
        "I can answer questions, provide information, or just have a friendly conversation."
    ]),
    # Using \b for age/old to match "age" or "old" as distinct words
    (r'(.*)\b(age|old)\b(.*)', ["I'm just a program, so I don't have an age!", "I was created recently, so I'm quite young!"]),
    # Using \b for weather/temperature
    (r'(.*)\b(weather|temperature)\b(.*)', [
        "I'm not connected to weather services, but I hope it's nice where you are!",
        "You might want to check a weather app for accurate forecasts."
    ]),
    # Using \b for science/technology/tech
    (r'(.*)\b(science|technology|tech)\b(.*)', [
        "Science and technology are fascinating! Did you know the first computer programmer was Ada Lovelace in the 1840s?",
        "Technology is advancing rapidly. AI like me is just one example of recent developments."
    ]),
    # Using \b for sports keywords
    (r'(.*)\b(sports|football|basketball|soccer)\b(.*)', [
        "I'm not much of a sports expert, but I know many people enjoy watching and playing sports!",
        "Sports are great for health and entertainment. Do you have a favorite team?"
    ]),
     # Using \b for music keywords
    (r'(.*)\b(music|song|band)\b(.*)', [
        "Music is wonderful! It can affect our moods and emotions.",
        "There are so many genres of music - pop, rock, classical, jazz... What do you like?"
    ]),
    # Using \b for movie/film
    (r'(.*)\b(movie|film)\b(.*)', [
        "Movies are a great way to tell stories. Do you prefer action, comedy, or drama?",
        "The first motion picture was made in the late 19th century. How far cinema has come!"
    ]),
    # Using \b for book/read/novel
    (r'(.*)\b(book|read|novel)\b(.*)', [
        "Reading expands the mind. What's the last book you enjoyed?",
        "Books can transport us to different worlds. I'm a fan of classic literature myself."
    ]),
    # Using \b for food keywords
    (r'(.*)\b(food|eat|cuisine)\b(.*)', [
        "Food is essential and delicious! Do you like cooking or prefer eating out?",
        "Every culture has its unique cuisine. What's your favorite dish?"
    ]),
    # Using \b for travel keywords
    (r'(.*)\b(travel|vacation|trip)\b(.*)', [
        "Traveling broadens our horizons. Where was your last vacation?",
        "There are so many beautiful places in the world to visit!"
    ]),
    # Using \b for joke/funny
    (r'(.*)\b(joke|funny)\b(.*)', [
        "Why don't scientists trust atoms? Because they make up everything!",
        "Why did the scarecrow win an award? Because he was outstanding in his field!"
    ]),
    # Using \b for thank you/thanks
    (r'(.*)\b(thank you|thanks)\b(.*)', ["You're welcome!", "No problem!", "Happy to help!"]),
    # Using \b for sorry/apologize
    (r'(.*)\b(sorry|apologize)\b(.*)', ["No need to apologize!", "It's alright!", "No worries!"]),
    # Using \b for love/like
    (r'(.*)\b(love|like)\b(.*)', ["That's wonderful to hear!", "Positive emotions are great!"]),
    # Using \b for hate/dislike
    (r'(.*)\b(hate|dislike)\b(.*)', ["I'm sorry to hear that.", "Sometimes we feel that way."]),
    # Using \b for help/support
    (r'(.*)\b(help|support)\b(.*)', ["I'll do my best to help. What do you need?", "How can I assist you?"]),
    # Using \b for time/date
    (r'(.*)\b(time|date)\b(.*)', ["I don't have access to real-time data, but you can check your device's clock!"]),
    # The general fallback pattern must be the last one and should match anything
    (r'(.*)', [
        "I see. Tell me more about that.",
        "Interesting! Can you elaborate?",
        "I understand. What else would you like to discuss?",
        "That's a good point. What's on your mind?"
    ])
]

# Initialize NLTK Chatbot with corrected patterns
chatbot = Chat(patterns, custom_reflections)

# Initialize Lemmatizer (kept from original code, though not used in this version of generate_response)
lemmatizer = WordNetLemmatizer()

# Helper function for WordNet POS tags (kept from original code)
def get_wordnet_pos(tag):
    """Map POS tags to WordNet tags"""
    if tag.startswith('J'):
        return wordnet.ADJ
    elif tag.startswith('V'):
        return wordnet.VERB
    elif tag.startswith('N'):
        return wordnet.NOUN
    elif tag.startswith('R'):
        return wordnet.ADV
    else:
        return None

# The generate_response function remains the same as the previous correction
# because the core issue was in the patterns, not the function's call to chatbot.respond()
def generate_response(message, history):
    """
    Generates a chatbot response based on the input message using NLTK Chat.
    Relies on the predefined patterns and reflections.
    Uses the fallback pattern (.*) if no specific pattern matches.
    """
    if not message or not isinstance(message, str):
        return "Please enter a valid message."

    # Use the NLTK Chat's respond method directly
    # With the (.*) pattern at the end, this method guarantees a response
    # for any non-empty input that doesn't match a preceding pattern.
    response = chatbot.respond(message)

    # Although chatbot.respond with (.*) guarantees a match for non-empty input,
    # a final check is added for robustness.
    if response is not None and response.strip() != "":
        return response
    else:
        # This fallback should only be reached if message is empty or chatbot.respond
        # returns None/empty for some unexpected reason.
        print(f"Warning: Fallback triggered for message: '{message}'") # Optional logging
        return random.choice([
            "I'm not sure how to respond to that.",
            "Could you please rephrase?",
            "Let's talk about something else."
        ])

# Setup Gradio Chat Interface
demo = gr.ChatInterface(
    fn=generate_response,
    title = "NLP Based Chatbot",
    description = "A simple UI based chatbot using NLTK Chat with improved patterns.",
    theme="soft"
)

# Launch the Gradio Interface (commented out for API usage)
demo.launch()

# To use via API, you would run your script and Gradio provides an API endpoint.
# The 'demo' object represents your Gradio application, which can be hosted.
# The `generate_response` function is the core logic callable with message and history.