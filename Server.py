from flask import Flask, request, jsonify
import subprocess
import json

app = Flask(__name__)

@app.route('/get_recommendations', methods=['POST'])
def get_recommendations():
    # Extract song and artist from the request
    data = request.json
    song = data.get('song')
    artist = data.get('artist')

    if not song or not artist:
        return jsonify({"error": "Song and artist are required."}), 400

    try:
        # Assuming your compiled C++ program is named 'song_recommender'
        # and it's in the same directory as your Flask app
        result = subprocess.run(['./main.exe', song, artist], capture_output=True, text=True)
        if result.returncode != 0:
            raise Exception(result.stderr)

        # Parse the C++ program's output as JSON
        recommendations = json.loads(result.stdout)

        return jsonify(recommendations)

    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)
