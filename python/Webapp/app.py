from flask import Flask, render_template, redirect, request
from flask_scss import Scss
from flask_sqlalchemy import SQLAlchemy
from unit16_converters import floatToUint16


# My App Setup
app = Flask(__name__)
Scss(app)
    
    
    
#Home Page
@app.route('/',methods=['POST', 'GET'])
def index():
    if request.method == 'POST':
        floatval = float(request.form['content'])
        
        try:
            uint16_1, uint16_2 = floatToUint16(floatval)
            return f"float {floatval} as unit16 is {uint16_1} and {uint16_2}"
        except Exception as e:
            print(f"ERROR: {e}")
            return f"ERROR: {e}"
    # See all current tasks
    else: 
        return render_template('index.html')

# Runner and Dubgger
if __name__ == '__main__':
    app.run(debug=True)