const reel = document.querySelector('.tab_reel');
const tab1header = document.querySelector('#homeTab')
const tab2header = document.querySelector('#savedTab')
const tab1 = document.querySelector('.tab1');
const tab2 = document.querySelector('.tab2');
const panel1 = document.querySelector('.tab_panel1');
const panel2 = document.querySelector('.tab_panel2');
const closeOutput = document.getElementById('closeOutput')
const Output = document.getElementById('output')

function slideLeft(e) {
  tab2.classList.remove('active');
  this.classList.add('active');
  tab2header.classList.remove('selectedTab')
  tab1header.classList.add('selectedTab')
  reel.style.transform = "translateX(0%)";
}

function slideRight(e) {
  tab1.classList.remove('active');
  this.classList.add('active');
  tab1header.classList.remove('selectedTab')
  tab2header.classList.add('selectedTab')
  reel.style.transform = "translateX(-50%)";
}

tab1.addEventListener('click', slideLeft);
tab2.addEventListener('click', slideRight);


document.addEventListener('DOMContentLoaded', function() {
  var submitButton = document.getElementById('submitForm');
  var form = document.getElementById('header-search-people');

  submitButton.addEventListener('click', function(event) {
      submitButton.classList.toggle('button--loading')
      event.preventDefault(); // Prevent the default button click behavior

      var songName = document.getElementById('fn').value;
      var artistName = document.getElementById('ln').value;

      var xhr = new XMLHttpRequest();
      xhr.open("POST", "http://localhost:5000/get_recommendations", true);
      xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
      
      xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 200) {
            var response = JSON.parse(xhr.responseText);
    
            // Filter out the searched song from recommendations if it's there
            var recommendations = response.recommendations.filter(function(recommendation) {
                return recommendation.title !== response.searchedSong.title || recommendation.artist !== response.searchedSong.artist;
            });
    
            // Clear existing recommendations
            var resultsDiv = document.getElementById('results');
            resultsDiv.innerHTML = '';
    
            // Iterate through the recommendations and create HTML elements
            recommendations.forEach(function(recommendation) {
                var songContainer = document.createElement('div');
                songContainer.className = 'songContainer';
    
             

                // Create box div with image
                var boxDiv = document.createElement('div');
                boxDiv.className = 'box';
                var img = document.createElement('img');
                img.src = 'https://t3.ftcdn.net/jpg/04/54/66/12/360_F_454661277_NtQYM8oJq2wOzY1X9Y81FlFa06DVipVD.jpg'; // Example image source
                img.alt = '';
                boxDiv.appendChild(img);
    
                // Create content div with title and artist
                var contentDiv = document.createElement('div');
                contentDiv.className = 'content';
                var titleH1 = document.createElement('h1');
                titleH1.textContent = recommendation.title;
                var artistP = document.createElement('p');
                artistP.textContent = recommendation.artist;
                contentDiv.appendChild(titleH1);
                contentDiv.appendChild(artistP);
    
                // Add additional elements as needed (like control div)
                var controlDiv = document.createElement('div');
                controlDiv.className = 'control';
                var wordIconAnchor = document.createElement('a');
                wordIconAnchor.href = '#';
                var wordIcon = document.createElement('i');
                wordIcon.className = 'fa-solid fa-file-word';
                wordIcon.style.cssText = 'color: #ffffff; font-size: 18px;';
                wordIconAnchor.appendChild(wordIcon);
                controlDiv.appendChild(wordIconAnchor);
            
                var youtubeIconAnchor = document.createElement('a');
                youtubeIconAnchor.href = '#';
                var youtubeIcon = document.createElement('i');
                youtubeIcon.className = 'fa-brands fa-youtube';
                youtubeIcon.style.cssText = 'color: #ffffff; font-size: 18px;';
                youtubeIconAnchor.appendChild(youtubeIcon);
                controlDiv.appendChild(youtubeIconAnchor);
            
                var musicIconAnchor = document.createElement('a');
                musicIconAnchor.href = '#';
                var musicIcon = document.createElement('i');
                musicIcon.className = 'fa-solid fa-cloud-music';
                musicIcon.style.cssText = 'color: #ffffff; font-size: 18px;';
                musicIconAnchor.appendChild(musicIcon);
                controlDiv.appendChild(musicIconAnchor);
                contentDiv.appendChild(controlDiv);
    
                //heart icon
                var saveThisDiv = document.createElement('div');
                saveThisDiv.className = 'saveThis';
                var heartIconAnchor = document.createElement('a');
                heartIconAnchor.href = '#';
                var heartIcon = document.createElement('i');
                heartIcon.className = 'fa-light fa-heart';
                heartIcon.style.cssText = 'color: #ffffff; font-size: 18px;';
                heartIconAnchor.appendChild(heartIcon);
                saveThisDiv.appendChild(heartIconAnchor);
                
    
                songContainer.appendChild(boxDiv);
                songContainer.appendChild(contentDiv);
                songContainer.appendChild(saveThisDiv);
                
    
                // Append songContainer to resultsDiv
                resultsDiv.appendChild(songContainer);
                document.getElementById("output").style.display = "block";
                submitButton.classList.remove('button--loading')
            });
        }
    };
    


    

      xhr.send(JSON.stringify({ song: songName, artist: artistName }));
  });
});


function closeOutputWindow(){
  Output.style.display = "none";
}

closeOutput.addEventListener('click', closeOutputWindow);

document.addEventListener('DOMContentLoaded', function() {
  var lyricsIcons = document.querySelectorAll('.fa-file-word');
  var youtubeIcons = document.querySelectorAll('.fa-youtube');
  var spotifyIcons = document.querySelectorAll('.fa-cloud-music');

  // Only this song at the moment just for demonstration
  var spotifyUrl = 'https://open.spotify.com/search/Alan%20Walker%20Alone';
  var geniusUrl = 'https://genius.com/search?q=Alan%20Walker%20Alone';
  var youtubeUrl = 'https://www.youtube.com/results?search_query=Alan+Walker+Alone';

  youtubeIcons.forEach(function(icon) {
      icon.parentElement.addEventListener('click', function(event) {
          event.preventDefault();
          window.open(youtubeUrl, '_blank');
      });
  });
  lyricsIcons.forEach(function(icon) {
      icon.parentElement.addEventListener('click', function(event) {
          event.preventDefault(); 
          window.open(geniusUrl, '_blank'); 
      });
  });
  spotifyIcons.forEach(function(icon) {
      icon.parentElement.addEventListener('click', function(event) {
          event.preventDefault(); 
          window.open(spotifyUrl, '_blank');
      });
  });
});
