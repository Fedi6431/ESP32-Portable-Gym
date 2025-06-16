// Load library
#include <WiFi.h>

// SSID & PSWD
const char* ssid = "ESP32-Gym";
const char* pswd = "calisthenics";

// AP configs
IPAddress localIp(192, 168, 1, 10);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Wifi web server
WiFiServer dioBanana(80);

void setup() {
  // Sets the data rate in bits per second (baud) for serial data transmission.
  Serial.begin(115200);

  Serial.println();
  Serial.println("Made by Fedi6431");
  Serial.println();

  // Set the configuration of the Access Point (AP)
  Serial.println("Setting " + String(ssid) + " AP configurations...");
  Serial.println("Status code : ");
  if (WiFi.softAPConfig(localIp, gateway, subnet)) {
    Serial.print("0");
  } else {
    Serial.print("999");
  }

  // Start the Access Point (AP)
  Serial.println("Starting " + String(ssid) + " AP...");
  Serial.println("Status code : ");
  if (WiFi.softAP(ssid, pswd)) {
    Serial.print("0");
  } else {
    Serial.print("909");
    exit(909);
  }

  // Print Access Point (AP) informations
  Serial.println(String(ssid) + " informations");
  Serial.println("SSID : " + String(ssid));
  Serial.println("PSWD : " + String(pswd));
  Serial.println("IP : " + WiFi.softAPIP());
  Serial.println("GATEWAY : " + String(gateway));
  Serial.println("SUBNET : " + String(subnet));
  Serial.println("MAC : " + WiFi.softAPmacAddress());
  Serial.println();

  dioBanana.begin();
}

void loop() {
  Serial.println(String(ssid) + " AP Server started with no errors");
  WiFiClient scimmia = dioBanana.accept(); // Listen for incoming clients

  if (scimmia) { // If a client connect
    Serial.println("New client connected!");
    String line = ""; // String for client data
    while (scimmia.connected()) { // Loop when client is connected
      if (scimmia.available()) {  // If there are bytes to read
        char c = scimmia.read(); // Read the bytes
        Serial.write(c); 
        line += c;
        if (c == '\n') {  // If the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (line.length() == 2) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            scimmia.println("HTTP/1.1 200 OK");
            scimmia.println("Content-type:text/html");
            scimmia.println("Connection: close");
            scimmia.println();

            // Send your "Hello World" HTML response
            scimmia.println("<html lang=\"en\">\n"
"<head><meta charset=\"UTF-8\"><meta name=\"author\" content=\"Fedi6431\"><meta name=\"description\" content=\"Free training scheduler\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Scheduled Training</title><style>.box {border: 2px solid black;border-radius: 10px;padding: 10px;text-align: center;margin: 10px;}.green {background-color: #00ff003d;}.red {background-color: #ff00003d;}.margin-top {margin-top: 10px;}.low-margin {margin-top: 5px;}</style></head>");
            scimmia.println("<body>\n"
"    <div class=\"box\">\n"
"        <h1>Exercise manager</h1>\n"
"        <h2>Exercises:</h2>\n"
"        <ul id=\"exerciseList\"></ul>\n"
"\n"
"        <!--EXERCISE MANAGER DIV-->\n"
"        <div>\n"
"            <br>\n"
"            <label for=\"ExerciseName\">Exercise Name:</label><br>\n"
"            <input type=\"text\" id=\"ExerciseName\" name=\"ExerciseName\" value=\"\"><br>\n"
"            <label for=\"reps\">Number of reps to do:</label><br>\n"
"            <input type=\"number\" id=\"objective\" name=\"objective\" min=\"1\"><br><br>\n"
"        </div>\n"
"\n"
"        <input type=\"button\" value=\"Add Exercise\" id=\"addExerciseBtn\">\n"
"        <input type=\"button\" value=\"Delete Exercise\" id=\"deleteExerciseBtn\">\n"
"    </div>\n"
"\n"
"    <!--EXAMPLE DIV-->\n"
"    <div class=\"box red\" id=\"exampleExercise\" style=\"display: none;\">\n"
"        <h1 class=\"exercise-title\">Exercise name</h1>\n"
"        <p><strong>Reps done: </strong><span class=\"reps-done\">0</span></p>\n"
"        <p><strong>Objective: </strong><span class=\"objective-number\">0</span></p>\n"
"        <input type=\"number\" class=\"add-rep\" min=\"1\" value=\"1\">\n"
"        <br>\n"
"        <input type=\"button\" value=\"Add rep numbers\" class=\"margin-top add-rep-btn\">\n"
"        <input type=\"button\" value=\"Clear rep numbers\" class=\"margin-top clear-reps-btn\">\n"
"    </div>\n"
"\n"
"    <script>\n"
"        const addExerciseBtn = document.getElementById('addExerciseBtn');\n"
"        const exerciseList = document.getElementById('exerciseList');\n"
"        const exampleExercise = document.getElementById('exampleExercise');\n"
"\n"
"        addExerciseBtn.addEventListener('click', () => {\n"
"            const exerciseName = document.getElementById('ExerciseName').value;\n"
"            const objective = parseInt(document.getElementById('objective').value);\n"
"\n"
"            if (exerciseName && objective > 0) {\n"
"                const newExerciseDiv = exampleExercise.cloneNode(true);\n"
"                newExerciseDiv.style.display = 'block';\n"
"                newExerciseDiv.querySelector('.exercise-title').textContent = exerciseName;\n"
"                newExerciseDiv.querySelector('.objective-number').textContent = objective;\n"
"                newExerciseDiv.querySelector('.reps-done').textContent = 0;\n"
"\n"
"                const addRepBtn = newExerciseDiv.querySelector('.add-rep-btn');\n"
"                const clearRepsBtn = newExerciseDiv.querySelector('.clear-reps-btn');\n"
"                const repsDoneSpan = newExerciseDiv.querySelector('.reps-done');\n"
"                const objectiveSpan = newExerciseDiv.querySelector('.objective-number');\n"
"                const addRepInput = newExerciseDiv.querySelector('.add-rep');\n"
"\n"
"                addRepBtn.addEventListener('click', () => {\n"
"                    const repsToAdd = parseInt(addRepInput.value);\n"
"                    let currentReps = parseInt(repsDoneSpan.textContent);\n"
"                    currentReps += repsToAdd;\n"
"                    repsDoneSpan.textContent = currentReps;\n"
"\n"
"                    if (currentReps >= objective) {\n"
"                        newExerciseDiv.classList.remove('red');\n"
"                        newExerciseDiv.classList.add('green');\n"
"                        addRepBtn.disabled = true; // Disable the button if the objective is met\n"
"                    }\n"
"                });\n"
"\n"
"                clearRepsBtn.addEventListener('click', () => {\n"
"                    repsDoneSpan.textContent = 0; // Reset reps done to 0\n"
"                    addRepBtn.disabled = false; // Re-enable the button\n"
"                    newExerciseDiv.classList.remove('green'); // Reset color to red\n"
"                });\n"
"\n"
"                exerciseList.appendChild(newExerciseDiv);\n"
"                document.getElementById('ExerciseName').value = ''; // Clear input field\n"
"                document.getElementById('objective').value = ''; // Clear objective field\n"
"            } else {\n"
"                alert('Please enter a valid exercise name and objective number.');\n"
"            }\n"
"        });\n"
"\n"
"        // Functionality for deleting exercises can be added here if needed\n"
"        // For now, we will just clear the input fields\n"
"        document.getElementById('deleteExerciseBtn').addEventListener('click', () => {\n"
"            const exercises = exerciseList.getElementsByClassName('box');\n"
"            if (exercises.length > 0) {\n"
"                exerciseList.removeChild(exercises[exercises.length - 1]); // Remove the last exercise added\n"
"            }\n"
"        });\n"
"    </script>\n"
"</body>\n"
"</html>");



            // The HTTP response ends with another blank line
            scimmia.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            line = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          line += c;      // add it to the end of the currentLine
        }
      }
    }
    // Close the connection
    scimmia.stop();
    Serial.println("Client disconnected!");
    Serial.println("");
  }
}
