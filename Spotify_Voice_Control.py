import serial
import spotipy
import spotipy.util as util
import json

# Load configuration from config.json
with open('config.json') as f:
    config = json.load(f)

# Spotify authentication
token = util.prompt_for_user_token(
    config['Spotify']['username'],
    config['Spotify']['scope'],
    config['Spotify']['client_id'],
    config['Spotify']['client_secret'],
    config['Spotify']['redirect_uri']
)

# Initialize Spotify client
spotify = spotipy.Spotify(auth=token)

# Initialize serial connection
arduino = serial.Serial(port=config['Arduino']['port'],
                        baudrate=config['Arduino']['baudRate'],
                        timeout=.1)

def execute_command(command):
    if command == 'playpause':
        spotify.play_pause()
    elif command == 'next':
        spotify.next_track()
    elif command == 'previous':
        try:
            spotify.previous_track()
        except spotipy.SpotifyException as e:
            print(f"Failed to go to previous track: {e}")
    else:
        print(f"Unknown command: {command}")

while True:
    if arduino.in_waiting > 0:
        command = arduino.readline().strip().decode('utf-8')
        print(f"Command received from Arduino: {command}")
        execute_command(command)
