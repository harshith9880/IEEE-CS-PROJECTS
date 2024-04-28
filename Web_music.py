from flask import Flask, render_template, request

app = Flask(__name__)

# Global variables
songs = [
    {"title": "Blinding Lights", "author": "The Weeknd", "lyrics": "Lyrics for Blinding Lights\n..."},
    {"title": "Save Your Tears", "author": "The Weeknd", "lyrics": "Lyrics for Save Your Tears\n..."},
    {"title": "Starboy", "author": "The Weeknd", "lyrics": "Lyrics for Starboy\n..."},
    {"title": "Heartless", "author": "The Weeknd", "lyrics": "Lyrics for Heartless\n..."},
    {"title": "In Your Eyes", "author": "The Weeknd", "lyrics": "Lyrics for In Your Eyes\n..."}
]
num_songs = len(songs)
current_song_index = 0
is_playing = False
volume = 1.0
recently_played = []

@app.route('/')
def index():
    return render_template('index.html', current_song=songs[current_song_index], is_playing=is_playing, volume=volume, recently_played=recently_played)

@app.route('/play_pause', methods=['POST'])
def play_pause():
    global is_playing
    is_playing = not is_playing
    return {'is_playing': is_playing}

@app.route('/next_song', methods=['POST'])
def next_song():
    global current_song_index
    current_song_index = (current_song_index + 1) % num_songs
    recently_played.append(songs[current_song_index])
    if len(recently_played) > 5:
        recently_played.pop(0)
    return {'current_song': songs[current_song_index], 'is_playing': is_playing}

@app.route('/prev_song', methods=['POST'])
def prev_song():
    global current_song_index
    current_song_index = (current_song_index - 1 + num_songs) % num_songs
    recently_played.append(songs[current_song_index])
    if len(recently_played) > 5:
        recently_played.pop(0)
    return {'current_song': songs[current_song_index], 'is_playing': is_playing}

@app.route('/increase_volume', methods=['POST'])
def increase_volume():
    global volume
    if volume < 1.0:
        volume += 0.1
    return {'volume': volume}

@app.route('/decrease_volume', methods=['POST'])
def decrease_volume():
    global volume
    if volume > 0.0:
        volume -= 0.1
    return {'volume': volume}

if __name__ == '__main__':
    app.run(debug=True)
