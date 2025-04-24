import nltk
import random
from nltk.tokenize import word_tokenize
from nltk.corpus import movie_reviews, stopwords
import string
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB

# Download required NLTK data
nltk.download('movie_reviews', quiet=True)
nltk.download('punkt', quiet=True)
nltk.download('stopwords', quiet=True)

# Step 3: Preprocess and Tokenize the Data
def preprocess_text(text):
    # Tokenize the text into individual words
    tokens = word_tokenize(text.lower())
    # Remove stopwords and punctuation
    stop_words = set(stopwords.words('english') + list(string.punctuation))
    filtered_tokens = [token for token in tokens if token not in stop_words]
    # Return the filtered tokens as a string
    return ' '.join(filtered_tokens)

# Step 5: Train a Machine Learning Model
# Create a list of (preprocessed text, category) tuples
corpus = [(preprocess_text(movie_reviews.raw(fileid)), category)
          for category in movie_reviews.categories()
          for fileid in movie_reviews.fileids(category)]

# Shuffle the corpus to ensure a random distribution
random.shuffle(corpus)

# Split the corpus into features and labels
texts, labels = zip(*corpus)

# Train a Multinomial Naive Bayes classifier
vectorizer = CountVectorizer()
X = vectorizer.fit_transform(texts)
clf = MultinomialNB()
clf.fit(X, labels)

# Step 6: Build your Chatbot
def generate_response(user_input):
    # Preprocess and tokenize the user input
    preprocessed_input = preprocess_text(user_input)
    input_vector = vectorizer.transform([preprocessed_input])
    # Use the classifier to predict a response
    predicted_category = clf.predict(input_vector)[0]
    # Choose a random movie review from the predicted category
    reviews_in_category = movie_reviews.fileids(predicted_category)
    review_id = random.choice(reviews_in_category)
    review_text = movie_reviews.raw(review_id)
    # Return the review text as the chatbot response
    return review_text

# Main loop for chatbot interaction
def run_chatbot():
    print("Movie Reviews Chatbot: Type 'exit' or 'quit' to stop.")
    while True:
        user_input = input("You: ").strip()
        if user_input.lower() in ["exit", "quit"]:
            print("Chatbot: Goodbye! Thanks for chatting!")
            break
        response = generate_response(user_input)
        print(f"Chatbot: {response[:200]}...")  # Truncate for readability

if __name__ == "__main__":
    run_chatbot()