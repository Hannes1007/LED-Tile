/*


  OK, ya ready for some fun? HTML + CSS styling + javascript all in and undebuggable environment

  one trick I've learned to how to debug HTML and CSS code.

  get all your HTML code (from html to /html) and past it into this test site
  muck with the HTML and CSS code until it's what you want
  https://www.w3schools.com/html/tryit.asp?filename=tryhtml_intro

  No clue how to debug javascrip other that write, compile, upload, refresh, guess, repeat

  I'm using class designators to set styles and id's for data updating
  for example:
  the CSS class .tabledata defines with the cell will look like
  <td><div class="tabledata" id = "switch"></div></td>

  the XML code will update the data where id = "switch"
  java script then uses getElementById
  document.getElementById("switch").innerHTML="Switch is OFF";


  .. now you can have the class define the look AND the class update the content, but you will then need
  a class for every data field that must be updated, here's what that will look like
  <td><div class="switch"></div></td>

  the XML code will update the data where class = "switch"
  java script then uses getElementsByClassName
  document.getElementsByClassName("switch")[0].style.color=text_color;


  the main general sections of a web page are the following and used here

  <html>
    <style>
    // dump CSS style stuff in here
    </style>
    <body>
      <header>
      // put header code for cute banners here
      </header>
      <main>
      // the buld of your web page contents
      </main>
      <footer>
      // put cute footer (c) 2021 xyz inc type thing
      </footer>
    </body>
    <script>
    // you java code between these tags
    </script>
  </html>


*/

// note R"KEYWORD( html page code )KEYWORD"; 
// again I hate strings, so char is it and this method let's us write naturally

const char PAGE_MAIN[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en" class="js-focus-visible">

<title>HexaTile LED Controller</title>

<style>
    table {
      position: relative;
      width:100%;
      border-spacing: 0px;
    }
    tr {
      border: 1px solid white;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
    }
    th {
      height: 20px;
      padding: 3px 15px;
      background-color: #343a40;
      color: #FFFFFF !important;
      }
    td {
      height: 20px;
       padding: 3px 15px;
    }
    .tabledata {
      font-size: 24px;
      position: relative;
      padding-left: 5px;
      padding-top: 5px;
      height:   25px;
      border-radius: 5px;
      color: #FFFFFF;
      line-height: 20px;
      transition: all 200ms ease-in-out;
      background-color: #00AA00;
    }
    .fanrpmslider {
      width: 100%;
      height: 55px;
      outline: none;
      height: 25px;
    }
    .bodytext {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 24px;
      text-align: left;
      font-weight: light;
      border-radius: 5px;
      display:inline;
    }
    .smalltext {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 16px;
      text-align: left;
      font-weight: light;
      border-radius: 5px;
      display:inline;
    }
    .navbar {
      width: 100%;
      height: 50px;
      margin: 0;
      padding: 10px 0px;
      background-color: #FFF;
      color: #000000;
      border-bottom: 5px solid #293578;
    }
    .fixed-top {
      position: fixed;
      top: 0;
      right: 0;
      left: 0;
      z-index: 1030;
    }
    .navtitle {
      float: left;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 50px;
      font-weight: bold;
      line-height: 50px;
      padding-left: 20px;
    }
   .navheading {
     position: fixed;
     left: 60%;
     height: 50px;
     font-family: "Verdana", "Arial", sans-serif;
     font-size: 20px;
     font-weight: bold;
     line-height: 20px;
     padding-right: 20px;
   }
   .navdata {
      justify-content: flex-end;
      position: fixed;
      left: 70%;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      font-weight: bold;
      line-height: 20px;
      padding-right: 20px;
   }
    .category {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: bold;
      font-size: 32px;
      line-height: 50px;
      padding: 20px 10px 0px 10px;
      color: #000000;
    }
    .heading {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: normal;
      font-size: 28px;
      text-align: left;
    }
  
    .btn {
      background-color: #444444;
      border: none;
      color: white;
      padding: 10px 20px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
    }
    .foot {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      position: relative;
      height:   30px;
      text-align: center;   
      color: #AAAAAA;
      line-height: 20px;
    }
    .container {
      max-width: 1800px;
      margin: 0 auto;
    }
    table tr:first-child th:first-child {
      border-top-left-radius: 5px;
    }
    table tr:first-child th:last-child {
      border-top-right-radius: 5px;
    }
    table tr:last-child td:first-child {
      border-bottom-left-radius: 5px;
    }
    table tr:last-child td:last-child {
      border-bottom-right-radius: 5px;
    }
</style>

<body style="background-color: #efefef" onload="process()">

    <header>
        <div class="navbar fixed-top">
            <div class="container">
                <div class="navtitle">HexaTile LED Controller</div>
                <div class="navdata" id="date">mm/dd/yyyy</div>
                <div class="navheading">DATE</div>
                <br>
                <div class="navdata" id="time">00:00:00</div>
                <div class="navheading">TIME</div>

            </div>
        </div>
    </header>

    <main class="container" style="margin-top:60px">
        <div class="category">Settings</div>
        <br>
        <div style="border-radius: 10px !important;">
            <table style="width:60%">
                <colgroup>
                    <col span="1" style="background-color:rgb(230,230,230); width: 40%; color:#000000 ;">
                    <col span="1" style="background-color:rgb(200,200,200); width: 25%; color:#000000 ;">
                    <col span="1" style="background-color:rgb(180,180,180); width: 25%; color:#000000 ;">
                    <col span="1" style="background-color:rgb(200,200,200); width: 10%; color:#000000 ;">
                </colgroup>
                <col span="2" style="background-color:rgb(0,0,0); color:#FFFFFF">
                <col span="2" style="background-color:rgb(0,0,0); color:#FFFFFF">
                <col span="2" style="background-color:rgb(0,0,0); color:#FFFFFF">
                <col span="2" style="background-color:rgb(0,0,0); color:#FFFFFF">
                           
                            <!-- Header -->
                            <tr>
                                <th colspan="1"><div class="heading">General</div></th>
                                <th colspan="1"><div class="heading"></div></th>
                                <th colspan="1"><div class="heading"></div></th>
                                <th colspan="1"><div class="heading"></div></th>
                            </tr>
                            <tr>
                                <td><div class="bodytext">Brightness</div></td>
                                <td><input type="range" id="brighnessSlider" class="fanrpmslider" min="0" max="255" value="100" width="0%" oninput="UpdateSliderBrightness(this.value)" /></td>
                                <td><div class="bodytext"><span id="brightness"></span></div>
                                <td><div class="bodytext"></div></td>
                            </tr>
                            <tr>
                                <td><div class="bodytext">Light Sensor Value</div></td>
                                <td><input type="range" id="lightSensorValueSlider" class="fanrpmslider" min="0" max="4100" value="150" width="0%" oninput="UpdateSliderLightSensorValue(this.value)" /></td>
                                <td><div class="bodytext"><span id="lightSensorValue"></span> </div>
                                <td><div class="bodytext"><span id="lightSensorValueR"></span> </div>
                            </tr>
                            <tr>
                                <td><div class="bodytext">Pir Sensor Time</div></td>
                                <td><input type="range" id="pirSensorTimeSlider" class="fanrpmslider" min="0" max="240" value="20" width="0%" oninput="UpdateSliderPirSensorTime(this.value)" /></td>
                                <td><div class="bodytext"><span id="pirSensorTime"></span></div>
                                <td><div class="bodytext"><span id="pirSensorTimeR"></span></div>
                            </tr>
            </table>
        </div>
        <br>

    </main>

    <main class="container" style="margin-top:20px">

        <div style="border-radius: 10px !important;">
            <table style="width:80%">
                <colgroup>
                    <col span="1" style="background-color:rgb(230,230,230); width: 15%; color:#000000 ;">
                    <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
                    <col span="1" style="background-color:rgb(180,180,180); width: 15%; color:#000000 ;">
                    <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
                    <col span="1" style="background-color:rgb(180,180,180); width: 15%; color:#000000 ;">
                    <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
                </colgroup>
                <col span="2" style="background-color:rgb(0,0,0); color:#FFFFFF">
                <col span="2" style="background-color:rgb(0,0,0); color:#FFFFFF">
                <col span="2" style="background-color:rgb(0,0,0); color:#FFFFFF">
                            
                            <!-- Header -->
                            <tr>
                                <th colspan="1"><div class="heading">Effects</div></th>
                                <th colspan="1"><div class="heading"></div></th>
                                <th colspan="1"><div class="heading"></div></th>
                                <th colspan="1"><div class="heading"></div></th>
                                <th colspan="1"><div class="heading"></div></th>
                                <th colspan="1"><div class="heading"></div></th>
                            </tr>

                            <!-- Dots -->
                            <tr>
                                <td><button type="button" class="btn" id="btnDots" onclick="ButtonPressDots()">Toggle</button></td>
                                <td><div class="bodytext">Dots</div></td>
                                <td><div class="smalltext">Primary Color</div><input type="color" class="fanrpmslider" id="dotsPValue" value="#e26715" oninput="UpdateColorPDots(this.value)" /></td>
                                <td><div class="smalltext">Secondary Color</div><input type="color" class="fanrpmslider" id="dotsSValue" value="#e26715" oninput="UpdateColorSDots(this.value)" /></td>
                                <td><div class="smalltext"></div></td>
                                <td><div class="smalltext"></div></td>
                            </tr>

                            <!-- Rain -->
                            <tr>
                                <td><button type="button" class="btn" id="btnRain" onclick="ButtonPressRain()">Toggle</button></td>
                                <td><div class="bodytext">Rain</div></td>
                                <td><div class="smalltext">Primary Color</div><input type="color" class="fanrpmslider" id="rainPValue" value="#e26715" oninput="UpdateColorPRain(this.value)" /></td>
                                <td><div class="smalltext">Secondary Color</div><input type="color" class="fanrpmslider" id="rainSValue" value="#e26715" oninput="UpdateColorSRain(this.value)" /></td>
                                <td><div class="smalltext">Amount per Tile</div> <div class="smalltext"><span id="rainAmount"></span></div> <input type="range" class="fanrpmslider" id="rainAmountSlider" min="0" max="10" value="3" width="0%" oninput="UpdateSliderRainAmount(this.value)" /></td>
                                <td><div class="smalltext">Speed</div> <div class="smalltext"><span id="rainSpeed"></span></div> <input type="range" class="fanrpmslider" id="rainSpeedSlider" min="0" max="100" value="20" width="0%" oninput="UpdateSliderRainSpeed(this.value)" />
                            </tr>

                            <!-- Noise -->
                            <tr>
                                <td><button type="button" class="btn" id="btnNoise" onclick="ButtonPressNoise()">Toggle</button></td>
                                <td><div class="bodytext">Noise</div></td>
                                <td><div class="smalltext">Primary Color</div><input type="color" class="fanrpmslider" id="noisePValue" value="#e26715" oninput="UpdateColorPNoise(this.value)" /></td>
                                <td><div class="smalltext">Secondary Color</div><input type="color" class="fanrpmslider" id="noiseSValue" value="#e26715" oninput="UpdateColorSNoise(this.value)" /></td>
                                <td><div class="smalltext">Resolution</div> <div class="smalltext"><span id="noiseResolution"></span></div> <input type="range" class="fanrpmslider" id="noiseResolutionSlider" min="0" max="100" value="50" width="0%" oninput="UpdateSliderNoiseResolution(this.value)" /></td>
                                <td><div class="smalltext">Speed</div> <div class="smalltext"><span id="noiseSpeed"></span></div> <input type="range" class="fanrpmslider" id="noiseSpeedSlider" min="0" max="100" value="20" width="0%" oninput="UpdateSliderNoiseSpeed(this.value)" />
                                </td>
                            </tr>
            </table>
        </div>
        <br>

    </main>

    <br>
    <footer div class="foot" id="temp">HexaTile LED Controller Settings | Hannes Herrmann | 2022</div>
    </footer>

</body>


<script type="text/javascript">
    // global variable visible to all java functions
    var xmlHttp=createXmlHttpObject();

    // function to create XML object
    function createXmlHttpObject(){
      if(window.XMLHttpRequest){
        xmlHttp=new XMLHttpRequest();
      }
      else{
        xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
      }
      return xmlHttp;
    }


    ////////////////////////
    // Buttons /////////////
    ////////////////////////    
  
    function ButtonPressDots() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      xhttp.open("PUT", "BUTTON_Dots", false);
      xhttp.send();
    }

    function ButtonPressRain() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      xhttp.open("PUT", "BUTTON_Rain", false);
      xhttp.send(); 
    }

    function ButtonPressNoise() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      xhttp.open("PUT", "BUTTON_Noise", false);
      xhttp.send(); 
    }
    
    ////////////////////////
    // Sliders /////////////
    ////////////////////////  
  
  //Brightness
    function UpdateSliderBrightness(value) {
      var xhttp = new XMLHttpRequest();

      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("brightnessValue").innerHTML=this.responseText;
        }
      }
      xhttp.open("PUT", "UPDATE_SLIDER_BRIGHTNESS?VALUE="+value, true);
      xhttp.send();
    }
  
  //LightSensorValue
    function UpdateSliderLightSensorValue(value) {
      var xhttp = new XMLHttpRequest();

      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("lightSensorValueValue").innerHTML=this.responseText;
        }
      }
      xhttp.open("PUT", "UPDATE_SLIDER_LIGHTSENSOR?VALUE="+value, true);
      xhttp.send();
    }
  
  //PirSensorTime
    function UpdateSliderPirSensorTime(value) {
      var xhttp = new XMLHttpRequest();

      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("pirSensorTimeValue").innerHTML=this.responseText;
        }
      }
      xhttp.open("PUT", "UPDATE_SLIDER_PIRSENSOR?VALUE="+value, true);
      xhttp.send();
    }
  
  //RainAmount
    function UpdateSliderRainAmount(value) {
      var xhttp = new XMLHttpRequest();

      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("rainAmountValue").innerHTML=this.responseText;
        }
      }
      xhttp.open("PUT", "UPDATE_SLIDER_RAINAMOUNT?VALUE="+value, true);
      xhttp.send();
    }

    //RainSpeed
    function UpdateSliderRainSpeed(value) {
      var xhttp = new XMLHttpRequest();

      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("rainSpeedValue").innerHTML=this.responseText;
        }
      }
      xhttp.open("PUT", "UPDATE_SLIDER_RAINSPEED?VALUE="+value, true);
      xhttp.send();
    }
  
  //NoiseResolution
    function UpdateSliderNoiseResolution(value) {
      var xhttp = new XMLHttpRequest();

      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("noiseResolutionValue").innerHTML=this.responseText;
        }
      }
      xhttp.open("PUT", "UPDATE_SLIDER_NOISERESOLUTION?VALUE="+value, true);
      xhttp.send();
    }
    
  //NoiseSpeed
    function UpdateSliderNoiseSpeed(value) {
      var xhttp = new XMLHttpRequest();

      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("noiseSpeedValue").innerHTML=this.responseText;
        }
      }
      xhttp.open("PUT", "UPDATE_SLIDER_NOISESPEED?VALUE="+value, true);
      xhttp.send();
    }

    ////////////////////////
    // Color Pickers ///////
    ////////////////////////  
  
  //Dots
    function UpdateColorPDots(value) {
      var xhttp = new XMLHttpRequest(); 
      value = value.substring(1);
      xhttp.open("PUT", "UPDATE_DOTS_PCOLOR?VALUE="+value, true);
      xhttp.send(); 
    }
    function UpdateColorSDots(value) {
      var xhttp = new XMLHttpRequest(); 
      value = value.substring(1);
      xhttp.open("PUT", "UPDATE_DOTS_SCOLOR?VALUE="+value, true);
      xhttp.send(); 
    }
  
  //Rain
    function UpdateColorPRain(value) {
      var xhttp = new XMLHttpRequest(); 
      value = value.substring(1);
      xhttp.open("PUT", "UPDATE_RAIN_PCOLOR?VALUE="+value, true);
      xhttp.send(); 
    }
    function UpdateColorSRain(value) {
      var xhttp = new XMLHttpRequest(); 
      value = value.substring(1);
      xhttp.open("PUT", "UPDATE_RAIN_SCOLOR?VALUE="+value, true);
      xhttp.send(); 
    }
  
  //Noise
    function UpdateColorPNoise(value) {
      var xhttp = new XMLHttpRequest(); 
      value = value.substring(1);
      xhttp.open("PUT", "UPDATE_NOISE_PCOLOR?VALUE="+value, true);
      xhttp.send(); 
    }
    function UpdateColorSNoise(value) {
      var xhttp = new XMLHttpRequest(); 
      value = value.substring(1);
      xhttp.open("PUT", "UPDATE_NOISE_SCOLOR?VALUE="+value, true);
      xhttp.send(); 
    }

    ////////////////////////
    // Response ////////////
    ////////////////////////  

    // function to handle the response from the ESP
    function response(){
      var message;
      var barwidth;
      var currentsensor;
      var xmlResponse;
      var xmldoc;
      var dt = new Date();
      var color = "#e8e8e8";
     
      // get the xml stream
      xmlResponse=xmlHttp.responseXML;
  
      // get host date and time
      document.getElementById("time").innerHTML = dt.toLocaleTimeString();
      document.getElementById("date").innerHTML = dt.toLocaleDateString();

      //Brightness
      xmldoc = xmlResponse.getElementsByTagName("BRIGHTNESSV");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("brightness").innerHTML=message + " / 255";
      document.getElementById("brighnessSlider").value = message;

      //LightSensorValue
      xmldoc = xmlResponse.getElementsByTagName("LIGHTSENSORV");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("lightSensorValue").innerHTML=message + " / 4100";
      document.getElementById("lightSensorValueSlider").value = message;

      //LightSensorValueR
      xmldoc = xmlResponse.getElementsByTagName("LIGHTSENSORVR");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("lightSensorValueR").innerHTML=message;

      //PirSensorTime
      xmldoc = xmlResponse.getElementsByTagName("PIRSENSORV");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("pirSensorTime").innerHTML=message + "s / 240s";
      document.getElementById("pirSensorTimeSlider").value = message;

      //PirSensorTimeR
      xmldoc = xmlResponse.getElementsByTagName("PIRSENSORVR");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("pirSensorTimeR").innerHTML=message + "s";
      
      //RainAmount
      xmldoc = xmlResponse.getElementsByTagName("RAINAMOUNTV");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("rainAmount").innerHTML=message;
      document.getElementById("rainAmountSlider").value = message;
     
      //RainSpeed
      xmldoc = xmlResponse.getElementsByTagName("RAINSPEEDV");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("rainSpeed").innerHTML=message;
      document.getElementById("rainSpeedSlider").value = message;

      //NoiseResolution
      xmldoc = xmlResponse.getElementsByTagName("NOISERESV");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("noiseResolution").innerHTML=message;
      document.getElementById("noiseResolutionSlider").value = message;

      //NoiseSpeed
      xmldoc = xmlResponse.getElementsByTagName("NOISESPEEDV");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("noiseSpeed").innerHTML=message;
      document.getElementById("noiseSpeedSlider").value = message;
      

      
      //DotsColor
      xmldoc = xmlResponse.getElementsByTagName("DOTSPCOLOR");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("dotsPValue").value = "#" + message;

      xmldoc = xmlResponse.getElementsByTagName("DOTSSCOLOR");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("dotsSValue").value = "#" + message;

      //RainColor
      xmldoc = xmlResponse.getElementsByTagName("RAINPCOLOR");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("rainPValue").value = "#" + message;

      xmldoc = xmlResponse.getElementsByTagName("RAINSCOLOR");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("rainSValue").value = "#" + message;

      //NoiseColor
      xmldoc = xmlResponse.getElementsByTagName("NOISEPCOLOR");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("noisePValue").value = "#" + message;

      xmldoc = xmlResponse.getElementsByTagName("NOISESCOLOR");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("noiseSValue").value = "#" + message;

      /////////////////
      // Buttons //////
      /////////////////
      
      xmldoc = xmlResponse.getElementsByTagName("EFFECTDOTS");
      message = xmldoc[0].firstChild.nodeValue;
      if (message == 0){
        document.getElementById("btnDots").innerHTML="Turned OFF";
        document.getElementById("btnDots").style.backgroundColor="#e6e6e6";
      }
      else{
        document.getElementById("btnDots").innerHTML="Turned ON";
        document.getElementById("btnDots").style.backgroundColor="#99C8FF";
      }

      xmldoc = xmlResponse.getElementsByTagName("EFFECTRAIN");
      message = xmldoc[0].firstChild.nodeValue;
      if (message == 0){
        document.getElementById("btnRain").innerHTML="Turned OFF";
        document.getElementById("btnRain").style.backgroundColor="#e6e6e6";
      }
      else{
        document.getElementById("btnRain").innerHTML="Turned ON";
        document.getElementById("btnRain").style.backgroundColor="#99C8FF";
      } 

      xmldoc = xmlResponse.getElementsByTagName("EFFECTNOISE");
      message = xmldoc[0].firstChild.nodeValue;
      if (message == 0){
        document.getElementById("btnNoise").innerHTML="Turned OFF";
        document.getElementById("btnNoise").style.backgroundColor="#e6e6e6";
      }
      else{
        document.getElementById("btnNoise").innerHTML="Turned ON";
        document.getElementById("btnNoise").style.backgroundColor="#99C8FF";
      } 


         
      xmldoc = xmlResponse.getElementsByTagName("SWITCH");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("switch").style.backgroundColor="rgb(200,200,200)";
      // update the text in the table
      if (message == 0){
        document.getElementById("switch").innerHTML="Switch is OFF";
        document.getElementById("btn1").innerHTML="Turn ON";
        document.getElementById("switch").style.color="#0000AA"; 
      }
      else {
        document.getElementById("switch").innerHTML="Switch is ON";
        document.getElementById("btn1").innerHTML="Turn OFF";
        document.getElementById("switch").style.color="#00AA00";
      }
     }
  
    // general processing code for the web page to ask for an XML steam
    // this is actually why you need to keep sending data to the page to 
    // force this call with stuff like this
    // server.on("/xml", SendXML);
    // otherwise the page will not request XML from the ESP, and updates will not happen
    function process(){
     
     if(xmlHttp.readyState==0 || xmlHttp.readyState==4) {
        xmlHttp.open("PUT","xml",true);
        xmlHttp.onreadystatechange=response;
        xmlHttp.send(null);
      }       
        // you may have to play with this value, big pages need more porcessing time, and hence
        // a longer timeout
        setTimeout("process()",100);
    }
</script>

</html>



)=====";
