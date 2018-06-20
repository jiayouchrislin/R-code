"""A simple data science web app

Here we create a simple Flask web application to perform machine learning and data visualization tasks.

To run this example:

    python app.py

And navigate to:

    http://localhost:5000

References:
    * Logo Nav Bootstrap 4 navigation template (https://startbootstrap.com/template-overviews/logo-nav/)
    * Model building and prediction (https://github.com/alichtner/nordstrom_flask)
    * Titanic Survival Dataset (https://www.kaggle.com/c/titanic/data)

Troubleshooting:
    * Make life easier: install Anaconda and run this example with Anaconda Prompt.
"""
# web framework: flask
from flask import Flask
from flask import render_template, request

# machine learning packages: pandas, numpy, scikit-learn
import pandas as pd
import numpy as np
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report

# plotting packages: matplotlib & seaborn
import io, base64
import matplotlib.pyplot as plt
import seaborn as sns

# create the Flask object
app = Flask(__name__)

# routes go here
# the @app.route('/') decorator ties the root URL to the home() function
# Therefore, when a user goes the root URL: http://localhost:5000/, the home() function is automatically invoked.
@app.route('/')
def home():
    # render_template() sends your data to a template and returns the rendered HTML to the browser
    return render_template('home.html')


# you can directly pass HTML inside
@app.route('/hello')
def hello():
    return "<h1>Hello World!</h1>"


# dynamically generate URLs and functionality
@app.route('/user/<username>')
def user_profile(username):
    return "<h1>Hello {}!</h1>".format(username)


# predict the probability of survival on Titanic
@app.route('/titanic', methods=['GET','POST'])
def titanic():
    data = {}   # data object to be passed back to the web page
    if request.form:
        # get the input data
        form_data = request.form
        data['form'] = form_data
        predict_class = float(form_data['predict_class'])
        predict_age = float(form_data['predict_age'])
        predict_sibsp = float(form_data['predict_sibsp'])
        predict_parch = float(form_data['predict_parch'])
        predict_fare = float(form_data['predict_fare'])
        predict_sex = 0 if form_data['predict_sex'] == 'M' else 1  # convert the sex from text to binary
        input_data = np.array([predict_class, predict_age, predict_sibsp, predict_parch, predict_fare, predict_sex])

        # get prediction
        prediction = model.predict_proba(input_data.reshape(1, -1))
        prediction = prediction[0][1] # probability of survival
        data['prediction'] = '{:.1%} Chance of Survival'.format(prediction)
        
    return render_template('titanic.html', data=data)


# show the data set (pandas dataframe)
@app.route('/table')
def table():
    table = titanic_df.head(30).to_html(index=False, na_rep='', classes="table table-striped")  # use the table class from bootstrap
    return render_template('table.html', contents=table)


# helper function for plotting
# return the plot as a string and embed that string directly in the HTML code.
def decode_image():
    img = io.BytesIO()  # use io.BytesIO to hold the stream (i.e., the plot file) in memory
    plt.savefig(img, format='png')  # save figure to the stream buffer
    plt.close()
    return base64.encodebytes(img.getvalue()).decode()


# plotting
@app.route('/plot')
def plot():
    df = titanic_df
    images = []

    ct = pd.crosstab(df['pclass'], df['survived'], margins=True)
    sns.heatmap(ct, annot=True, fmt='d', cmap='Blues', vmax=1000)
    images.append(decode_image())

    sns.boxplot(x='pclass', y='fare', data=df)
    images.append(decode_image())

    sns.boxplot(x='pclass', y='age', data=df)
    images.append(decode_image())

    sns.violinplot(x='survived', y='age', hue='sex', data=df, split=True, palette="Set1")
    images.append(decode_image())

    return render_template('plot.html', images=images)

# initialize: build a basic model for Titanic survival
def init():
    # preprocess
    titanic_df['sex_binary'] = titanic_df['sex'].map({'female': 1, 'male': 0})

    # choose features and create test and train sets
    features = ['pclass', 'age', 'sibsp', 'parch', 'fare', 'sex_binary']
    target = 'survived'
    sub_df = titanic_df[features + [target]].dropna()

    train_df, test_df = train_test_split(sub_df)
    X_train = train_df[features]
    y_train = train_df[target]
    X_test = test_df[features]
    y_test = test_df[target]

    # fit the model
    model = LogisticRegression()
    model.fit(X_train, y_train)

    # check the performance
    target_names = ['Died', 'Survived']
    y_pred = model.predict(X_test)
    print(classification_report(y_test, y_pred, target_names=target_names))

    return model


# App main entry
if __name__ == '__main__':
    # initialize: load data
    titanic_df = pd.read_csv('data/titanic_data.csv')

    # initialize: build a machine learning model
    model = init()

    # start the app
    # With debug enabled, Flask will automatically check for code changes and auto-reload these changes
    # No need to kill Flask and restart it each time you make code changes!
    app.run(debug=True)
