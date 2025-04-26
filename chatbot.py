import nltk
import re
import random
from nltk.tokenize import word_tokenize
from nltk.tag import pos_tag
from datetime import datetime

# Download required NLTK data (ensure these are downloaded once)
# You might need to run nltk.download('punkt') and nltk.download('averaged_perceptron_tagger')
# separately the first time you run this code.
try:
    nltk.data.find('tokenizers/punkt')
except nltk.downloader.DownloadError:
    nltk.download('punkt')
except LookupError:
     nltk.download('punkt')

try:
    nltk.data.find('taggers/averaged_perceptron_tagger')
except nltk.downloader.DownloadError:
    nltk.download('averaged_perceptron_tagger')
except LookupError:
    nltk.download('averaged_perceptron_tagger')


class RestaurantChatbot:
    def __init__(self):
        # Store reservations: {name: {date, time, party_size}}
        self.reservations = {}

        # Menu structure
        self.menu = {
            'vegetarian': ['Veggie Pizza', 'Pasta Primavera'],
            'non-vegetarian': ['Chicken Alfredo', 'Grilled Salmon'],
            'dessert': ['Chocolate Cake', 'Tiramisu']
        }

        # FAQ structure
        self.faq = {
            'hours': 'We are open from 10 AM to 10 PM daily.',
            'location': '123 Flavor Street, Food City.',
            'reservations': 'You can book a table by telling me your name, date, time, and party size!'
        }

        # --- Core Intent Keywords ---
        # Using keywords and POS tags to guide intent identification
        self.intent_keywords = {
            'book': ['book', 'reserve', 'reservation', 'table'],
            'menu': ['menu', 'food', 'dishes', 'eat'],
            'faq': ['hours', 'open', 'close', 'location', 'where', 'when', 'address'],
            'greeting': ['hello', 'hi', 'hey', 'greetings'],
            'farewell': ['bye', 'goodbye']
        }

        # --- Entity Extraction Patterns (using regex) ---
        # These are still needed but are more focused on finding specific data types
        self.entity_patterns = {
            'name': r'(?:i am|my name is)\s+([A-Z][a-z]+)', # Look for Name after "I am" or "my name is"
            'party_size': r'\b(\d+)\b', # Look for numbers for party size
            'time': r'\b(\d{1,2}(:\d{2})?\s*(?:am|pm))\b', # Look for time patterns (7pm, 7:00pm)
            'date': r'\b(today|tomorrow|\d{1,2}/\d{1,2})\b' # Look for date patterns
        }


    def tokenize_and_tag(self, text):
        """Tokenize and POS tag the input text using NLTK."""
        tokens = word_tokenize(text)
        tagged = pos_tag(tokens)
        return tagged

    def extract_entities(self, text, tagged_text):
        """Extract entities using regex patterns and potentially POS tags."""
        entities = {'name': None, 'date': None, 'time': None, 'party_size': None}

        # Use regex patterns first for specific formats
        for entity_type, pattern in self.entity_patterns.items():
            match = re.search(pattern, text, re.IGNORECASE)
            if match:
                entities[entity_type] = match.group(1)

        # Fallback/Enhancement using POS tags for Name and Date (day names)
        if not entities['name']:
             # Look for Proper Nouns (NNP) as potential names
             for word, pos in tagged_text:
                 if pos == 'NNP' and word not in {'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday'}: # Exclude day names
                     entities['name'] = word
                     break # Take the first potential name

        if not entities['date']:
            # Look for day names (Monday, Tuesday, etc.)
            for word, pos in tagged_text:
                if pos in ['NNP', 'NN'] and word.lower() in ['monday', 'tuesday', 'wednesday', 'thursday', 'friday', 'saturday', 'sunday']:
                    entities['date'] = word.capitalize()
                    break # Take the first day name found


        # Provide default values if entities are still missing
        if not entities['name']:
             entities['name'] = f"Guest_{random.randint(1000, 9999)}"
        if not entities['date']:
             entities['date'] = datetime.now().strftime("%d/%m") # Default to today
        if not entities['time']:
             entities['time'] = "7:00pm" # Default time
        if not entities['party_size']:
             entities['party_size'] = "2" # Default party size


        return entities

    def classify_intent(self, tagged_text):
        """Classify the user's intent based on keywords and POS tags."""
        # Look for core verbs or nouns indicating intent
        text_lower = " ".join([word.lower() for word, pos in tagged_text])

        if any(word in text_lower for word in self.intent_keywords['greeting']):
            return 'greeting'
        elif any(word in text_lower for word in self.intent_keywords['farewell']):
            return 'farewell'
        elif any(word in text_lower for word in self.intent_keywords['book']):
             return 'booking'
        elif any(word in text_lower for word in self.intent_keywords['menu']):
             # Check for specific menu categories within menu intent
             if 'vegetarian' in text_lower or 'vegan' in text_lower:
                 return 'menu_vegetarian'
             elif 'dessert' in text_lower:
                 return 'menu_dessert'
             else:
                 return 'menu_full'
        elif any(word in text_lower for word in self.intent_keywords['faq']):
             # Check for specific FAQ types within faq intent
             if 'hours' in text_lower or 'open' in text_lower or 'close' in text_lower:
                 return 'faq_hours'
             elif 'location' in text_lower or 'where' in text_lower or 'address' in text_lower:
                 return 'faq_location'
             else:
                 return 'faq_reservations' # Default FAQ if general FAQ words used

        # If no specific intent matched, return default
        return 'default'


    def respond(self, text):
        """Process user input and generate a response using NLTK."""
        text = text.strip()
        if not text:
            return "Please say something!"

        # Tokenize and tag the input
        tagged_text = self.tokenize_and_tag(text)

        # Classify the intent
        intent = self.classify_intent(tagged_text)

        # Handle response based on classified intent
        if intent == 'greeting':
            return "Hi! Welcome to our restaurant. How can I assist you today?"

        elif intent == 'farewell':
            return "Goodbye! Thanks for visiting us!"

        elif intent == 'booking':
            entities = self.extract_entities(text, tagged_text)
            name = entities['name']
            date = entities['date']
            time = entities['time']
            party_size = entities['party_size']

            # Store reservation
            self.reservations[name] = {
                'date': date,
                'time': time,
                'party_size': party_size
            }

            details = f"Name: {name}, Date: {date}, Time: {time}, Party Size: {party_size}"
            return f"I've booked your table! Details: {details}"

        elif intent == 'menu_full':
             response = (f"Vegetarian: {', '.join(self.menu['vegetarian'])}\n"
                         f"Non-Vegetarian: {', '.join(self.menu['non-vegetarian'])}\n"
                         f"Desserts: {', '.join(self.menu['dessert'])}")
             return f"Here's our menu:\n{response}"

        elif intent == 'menu_vegetarian':
            response = ', '.join(self.menu['vegetarian'])
            return f"Our vegetarian options include: {response}"

        elif intent == 'menu_dessert':
            response = ', '.join(self.menu['dessert'])
            return f"Our dessert options include: {response}"

        elif intent == 'faq_hours':
            return self.faq['hours']

        elif intent == 'faq_location':
            return self.faq['location']

        elif intent == 'faq_reservations':
            return self.faq['reservations']

        elif intent == 'default':
            return "I'm not sure I understood. Could you say that again or ask about reservations, menu, or hours?"

# --- Main Execution ---
def main():
    chatbot = RestaurantChatbot()
    print("Welcome to the NLTK Integrated Restaurant Chatbot! Type 'exit' to quit.")

    while True:
        user_input = input("You: ")
        if user_input.lower() == 'exit':
            print("Chatbot: Goodbye! Thanks for visiting!")
            break
        response = chatbot.respond(user_input)
        print(f"Chatbot: {response}")

if __name__ == "__main__":
    main()
