import serial
from flask import Flask, render_template, request, jsonify

app = Flask(__name__)

SERIAL_PORT = 'COM7'  # atualize conforme a porta correta
BAUD_RATE = 9600

def send_to_arduino(data_str):
    try:
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
            ser.write(data_str.encode())
    except serial.SerialException as e:
        print(f"Erro ao comunicar com o Arduino: {e}")

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/control', methods=['POST'])
def control():
    data = request.get_json()
    if 'servo_angle' in data:
        angle = data['servo_angle']
        print(f"Servo angle: {angle}")
        send_to_arduino(f'S:{angle}\n')  # Envia algo como: S:90
    if 'led_r' in data and 'led_g' in data and 'led_b' in data:
        r, g, b = data['led_r'], data['led_g'], data['led_b']
        print(f"LED RGB: R{r} G{g} B{b}")
        send_to_arduino(f'L:{r},{g},{b}\n')  # Envia algo como: L:255,0,0
    return jsonify(success=True)

if __name__ == '__main__':
    app.run(debug=True)
