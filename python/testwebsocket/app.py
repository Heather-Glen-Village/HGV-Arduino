# app.py
from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import requests

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

# Get stock data from API
def get_stock_data():
    response = requests.get('ws://127.0.0.1:1880/sensor')
    return response.json()

@socketio.on('connect')
def handle_connect():
    print('Client connected')
    emit('message', 'Hello, client!')
    emit('stock_data', get_stock_data())

@socketio.on('disconnect')
def handle_disconnect():
    print('Client disconnected')

@app.route('/')
def index():
    return get_stock_data()

if __name__ == '__main__':
    socketio.run(app)