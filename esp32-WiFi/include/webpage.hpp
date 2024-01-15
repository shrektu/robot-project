const char* htmlHomePage PROGMEM = R"HTMLHOMEPAGE(
<!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
    <style>
      .arrows {
        font-size: 70px;
        color: red;
      }
      td {
        background-color: black;
        border-radius: 25%;
        box-shadow: 5px 5px #888888;
      }
      td:active {
        transform: translate(5px, 5px);
        box-shadow: none;
      }
      .noselect {
        -webkit-touch-callout: none;
        -webkit-user-select: none;
        -khtml-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
      }
    </style>
  </head>
  <body class="noselect" align="center" style="background-color: white">

    <h1 style="color: black; text-align: center;">Transmitator</h1>

    <table id="mainTable" style="width:400px; margin:auto; table-layout:fixed" CELLSPACING=10>
      <tr>
        <td style="background-color: white; box-shadow: 0px 0px"></td>
        <td ontouchstart='onTouchStartAndEnd(1)' ontouchend='onTouchStartAndEnd(0)'><span class="arrows" >&#8678;</span></td>
        <td style="background-color: white; box-shadow: 0px 0px"></td>
      </tr>

      <tr>
        <td ontouchstart='onTouchStartAndEnd(3)' ontouchend='onTouchStartAndEnd(0)'><span class="arrows" >&#8678;</span></td>
        <td ontouchstart='onTouchStartAndEnd(2)' ontouchend='onTouchStartAndEnd(0)'><span class="arrows" >&#8681;</span></td>
        <td ontouchstart='onTouchStartAndEnd(4)' ontouchend='onTouchStartAndEnd(0)'><span class="arrows" >&#8680;</span></td>
      </tr>

      <tr>
        <td ontouchstart='onTouchStartAndEnd(5)' ontouchend='onTouchStartAndEnd(0)'><span class="arrows" >T</span></td>
        <td ontouchstart='onTouchStartAndEnd(6)' ontouchend='onTouchStartAndEnd(0)'><span class="arrows" >P</span></td>
        <td ontouchstart='onTouchStartAndEnd(7)' ontouchend='onTouchStartAndEnd(0)'><span class="arrows" >D</span></td>
      </tr>
    </table>

    <script>
      var webSocketUrl = "ws:\/\/" + window.location.hostname + "/ws";
      var websocket;

      function initWebSocket() {
        websocket = new WebSocket(webSocketUrl);
        websocket.onopen    = function (event) {};
        websocket.onclose   = function (event) { setTimeout(initWebSocket, 2000); };
        websocket.onmessage = function (event) {};
      }

      function onTouchStartAndEnd(value) {
        websocket.send(value);
      }

      window.onload = initWebSocket;
      document.getElementById("mainTable").addEventListener("touchend", function (event) {
        event.preventDefault()
      });
    </script>

  </body>
</html>
)HTMLHOMEPAGE";
