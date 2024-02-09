const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>LG Remote</title>
    <style>
      @import url("https://fonts.googleapis.com/css2?family=Open+Sans:wght@300;500&display=swap");
      *,
      *::before,
      *::after {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
      }

      body {
        font-family: "Open Sans", sans-serif;

        background-image: linear-gradient(
          0deg,
          rgba(0, 0, 0, 1) 0%,
          rgba(121, 9, 9, 1) 100%
        );
      }

      body::before {
        content: "";
        position: fixed;
        top: 0;
        left: 0;
        height: 100%;
        width: 100%;
        background-image: linear-gradient(
          0deg,
          rgba(0, 104, 255, 1) 0%,
          rgba(0, 175, 255, 1) 100%
        );
        opacity: 0;
        transition: opacity 1s ease-in-out;
      }

      .powerON::before {
        opacity: 1;
      }

      button {
        padding: 1.25rem 1.75rem;
        border: none;
        cursor: pointer;
        color: rgb(29, 43, 49);
        background-color: rgb(120, 184, 214);
        border-radius: 1rem;
      }

      button:is(:hover, :active) {
        background-color: rgba(120, 184, 214, 0.5);
      }

      @media (hover: none) {
        button:is(:hover, :active) {
          background-color: rgb(120, 184, 214);
        }
      }

      .title {
        position: fixed;
        top: 0;
        left: 0;
        margin: 0.5rem 1rem;
        color: rgba(255, 255, 255, 0.5);
      }

      .offline {
        position: relative;
        display: none;
        flex-direction: column;
        justify-content: center;
        align-items: center;
        height: 100vh;
        overflow: hidden;
        z-index: 10;
      }

      .offline svg {
        width: 50%;
        height: 50%;
      }

      .offline button {
        font-size: x-large;
      }

      .container {
        width: 100vw;
        height: 100vh;
        position: relative;
        display: flex;
        flex-direction: column;
        justify-content: center;
      }

      .info {
        width: 100%;
        display: flex;
        flex-direction: column;
        justify-content: center;
        position: absolute;
        top: 35%;
        left: 50%;
        transform: translate(-50%, -50%);
      }

      .temp {
        color: white;
        font-size: 8rem;
        text-align: center;
      }

      .timer-info {
        font-size: 2rem;
        text-align: center;
        color: rgba(255, 255, 255, 0.5);
        visibility: hidden;
      }

      .power-button {
        margin-top: 2rem;
        align-self: center;
        width: auto;
      }

      .buttons {
        align-self: center;
        margin-top: auto;
        display: flex;
        flex-direction: column;
        align-items: center;
        margin-bottom: 3rem;
      }

      .temp-buttons {
        display: flex;
        gap: 0.5rem;
        margin-bottom: 1rem;
      }

      .temp-button {
        display: flex;
        justify-content: center;
        align-items: center;
      }

      .other-buttons {
        display: flex;
        gap: 0.5rem;
      }

      .other-button {
        display: flex;
        justify-content: center;
        align-items: center;
      }

      .modal {
        visibility: hidden;
        opacity: 0;
        position: fixed;
        inset: 0;
        display: flex;
        justify-content: center;
        align-items: center;
        transition: all 0.2s;
      }

      .modal:target {
        visibility: visible;
        opacity: 1;
      }

      .modal-content {
        width: 80%;
        max-width: 325px;
        background-color: aliceblue;
        position: relative;
        padding: 2rem;
        padding-top: 5rem;
        display: flex;
        flex-direction: column;
        gap: 1rem;
        border-radius: 1rem;
      }

      .modal > a {
        position: relative;
        display: block;
      }

      .modal > a::before {
        left: 0;
        top: 0;
        width: 100%;
        height: 100%;
        position: fixed;
        background-color: rgba(0, 0, 0, 0.7);
        content: "";
        cursor: default;
      }

      .modal-content > a {
        position: absolute;
        top: 0.75rem;
        right: 0.75rem;
        text-decoration: none;
        color: gray;
      }

      .modal-content button {
        flex: 0 1 2rem;
        font-size: x-large;
      }

      .modal-content select {
        font-size: x-large;
      }
    </style>
  </head>
  <body onload="getData()">
    <main>
      <p class="title">LG A/C Remote</p>
      <div class="offline">
        <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 256 256">
          <rect width="256" height="256" fill="none" />
          <line
            x1="48"
            y1="40"
            x2="208"
            y2="216"
            fill="none"
            stroke="#fff"
            stroke-linecap="round"
            stroke-linejoin="round"
            stroke-width="24"
          />
          <path
            d="M25,98.2A147.2,147.2,0,0,1,72.4,66.9"
            fill="none"
            stroke="#fff"
            stroke-linecap="round"
            stroke-linejoin="round"
            stroke-width="24"
          />
          <path
            d="M59,132.1A98.3,98.3,0,0,1,108,106"
            fill="none"
            stroke="#fff"
            stroke-linecap="round"
            stroke-linejoin="round"
            stroke-width="24"
          />
          <path
            d="M92.9,166.1a50.9,50.9,0,0,1,67.6-2.4"
            fill="none"
            stroke="#fff"
            stroke-linecap="round"
            stroke-linejoin="round"
            stroke-width="24"
          />
          <path
            d="M117,56.4c3.6-.3,7.3-.4,11-.4A145.6,145.6,0,0,1,230.9,98.2"
            fill="none"
            stroke="#fff"
            stroke-linecap="round"
            stroke-linejoin="round"
            stroke-width="24"
          />
          <path
            d="M167.8,112.3A99.2,99.2,0,0,1,197,132.1"
            fill="none"
            stroke="#fff"
            stroke-linecap="round"
            stroke-linejoin="round"
            stroke-width="24"
          />
          <circle cx="128" cy="200" r="16" fill="#fff" />
        </svg>
        <button onclick="getData()">Retry</button>
      </div>
      <div class="container">
        <div class="info">
          <h1 class="temp"></h1>
          <p class="timer-info">Sleeps at <span>0</span></p>
          <button onclick="togglePower()" class="power-button">
            <svg
              xmlns="http://www.w3.org/2000/svg"
              fill="none"
              viewBox="0 0 24 24"
              stroke-width="2"
              stroke="currentColor"
              width="2rem"
              height="2rem"
            >
              <path
                stroke-linecap="round"
                stroke-linejoin="round"
                d="M5.636 5.636a9 9 0 1012.728 0M12 3v9"
              />
            </svg>
          </button>
        </div>
        <div class="buttons">
          <div class="temp-buttons">
            <button onclick="swing()" class="temp-button">
              <svg
                version="1.0"
                xmlns="http://www.w3.org/2000/svg"
                width="2rem"
                height="2rem"
                viewBox="0 0 512.000000 512.000000"
                preserveAspectRatio="xMidYMid meet"
              >
                <g
                  transform="translate(0.000000,512.000000) scale(0.100000,-0.100000)"
                  fill="#000000"
                  stroke="none"
                >
                  <path
                    d="M3416 4901 c-4 -5 -2 -61 4 -123 33 -347 171 -653 408 -900 207 -215
             449 -355 735 -423 114 -27 326 -50 339 -37 5 5 7 53 6 108 l-3 99 -96 7 c-620
             44 -1133 555 -1177 1173 l-7 100 -102 3 c-58 1 -104 -1 -107 -7z"
                  />
                  <path
                    d="M1906 4149 c-730 -267 -1092 -396 -1097 -388 -3 6 -37 96 -75 200
             -38 103 -72 185 -75 181 -10 -10 -439 -937 -439 -948 0 -8 951 -455 957 -450
             1 1 -31 91 -72 201 -40 110 -72 201 -71 202 1 1 211 79 466 172 1200 438 1723
             630 1728 635 3 3 -20 59 -50 123 -77 163 -109 254 -152 446 -4 15 -12 27 -19
             26 -6 0 -502 -180 -1101 -400z m1000 22 c18 -52 32 -96 31 -97 -1 -2 -491
             -181 -1087 -400 -597 -218 -1086 -397 -1088 -399 -1 -1 7 -28 18 -60 11 -32
             20 -59 20 -61 0 -4 -284 128 -293 136 -10 8 123 301 134 294 4 -2 15 -27 24
             -54 9 -28 21 -50 26 -50 9 0 1985 721 2094 765 33 13 66 23 74 22 7 -1 28 -44
             47 -96z"
                  />
                  <path
                    d="M2508 2963 l-828 -828 -148 148 c-81 81 -151 147 -155 147 -4 0 -7
             -238 -7 -530 l0 -530 530 0 c292 0 530 3 530 7 0 4 -66 74 -147 155 l-148 148
             830 830 c456 456 827 831 825 833 -3 3 -40 32 -82 66 -102 80 -219 197 -297
             296 -35 44 -66 81 -70 83 -3 1 -378 -370 -833 -825z m892 432 l75 -75 -820
             -820 -820 -820 45 -45 44 -45 -167 0 -167 0 0 167 0 167 45 -44 45 -45 818
             818 c449 449 819 817 822 817 3 0 39 -34 80 -75z"
                  />
                  <path
                    d="M3922 3148 c-117 -322 -773 -2113 -775 -2114 -1 -1 -92 32 -202 72
             -109 40 -200 72 -201 71 -5 -6 443 -957 451 -957 11 0 936 428 947 438 4 4
             -83 40 -193 81 -121 44 -199 78 -196 85 97 254 799 2188 796 2191 -3 2 -59 18
             -124 35 -130 34 -257 81 -377 141 -43 22 -82 39 -87 39 -5 0 -23 -37 -39 -82z
             m248 -242 c75 -27 95 -38 94 -53 -1 -10 -177 -499 -392 -1086 -216 -588 -392
             -1072 -392 -1077 0 -5 22 -16 50 -25 27 -9 52 -20 54 -24 5 -7 -267 -136 -286
             -136 -8 0 -148 286 -143 293 1 1 28 -7 60 -18 32 -11 59 -19 60 -18 2 2 182
             492 400 1091 219 598 399 1087 399 1087 1 0 44 -15 96 -34z"
                  />
                </g>
              </svg>
            </button>
            <button onclick="increment()" class="temp-button">
              <svg
                xmlns="http://www.w3.org/2000/svg"
                fill="none"
                viewBox="0 0 24 24"
                stroke-width="2"
                stroke="currentColor"
                width="2rem"
                height="2rem"
              >
                <path
                  stroke-linecap="round"
                  stroke-linejoin="round"
                  d="M4.5 15.75l7.5-7.5 7.5 7.5"
                />
              </svg>
            </button>
            <button onclick="fan()" class="other-button">
              <svg
                version="1.0"
                xmlns="http://www.w3.org/2000/svg"
                width="2rem"
                height="2rem"
                viewBox="0 0 512 512"
              >
                <g
                  transform="translate(0,512) scale(0.1,-0.1)"
                  stroke="currentColor"
                  stroke-width="200"
                >
                  <path
                    d="M2273 4964 c-597 -72 -1160 -373 -1551 -829 -491 -572 -689 -1360
             -526 -2094 82 -372 271 -754 517 -1046 453 -538 1139 -855 1847 -855 546 0
             1091 192 1520 537 485 388 812 983 885 1609 92 790 -222 1590 -830 2112 -291
             250 -677 442 -1056 526 -246 55 -559 70 -806 40z m525 -134 c776 -83 1454
             -554 1805 -1256 172 -345 246 -690 234 -1094 -10 -342 -78 -612 -231 -925
             -116 -235 -229 -396 -406 -579 -352 -363 -764 -579 -1285 -672 -143 -26 -567
             -26 -710 0 -242 43 -431 104 -640 205 -234 113 -407 234 -594 416 -354 344
             -570 753 -662 1255 -26 139 -36 455 -20 611 93 897 706 1658 1561 1937 159 53
             298 82 495 105 69 9 363 6 453 -3z"
                  />
                  <path
                    d="M1874 4230 c-194 -27 -356 -111 -489 -252 -84 -90 -128 -161 -166
             -270 -37 -110 -52 -211 -47 -329 5 -134 10 -139 137 -139 326 0 594 -115 736
             -315 29 -41 45 -72 42 -83 -3 -9 -17 -46 -30 -82 -14 -36 -28 -90 -32 -121 -7
             -54 -8 -57 -53 -78 -89 -43 -267 -169 -354 -250 -204 -191 -304 -387 -315
             -616 -6 -130 10 -231 56 -351 92 -238 315 -440 557 -505 120 -32 289 -30 409
             5 167 50 327 145 333 198 2 19 -13 54 -47 110 -167 275 -195 583 -75 821 22
             42 28 47 59 47 46 0 130 19 179 40 l41 17 110 -58 c141 -73 274 -122 405 -149
             88 -18 128 -21 245 -17 156 5 220 19 333 72 238 112 439 337 498 556 26 98 24
             255 -5 349 -45 149 -138 289 -271 413 -71 66 -178 142 -243 173 -34 16 -41 17
             -64 4 -29 -17 -26 -12 -81 -131 -97 -211 -332 -371 -633 -433 l-63 -13 -43 58
             c-24 31 -66 74 -93 95 l-50 38 0 129 c0 384 -123 705 -338 883 -82 68 -220
             138 -326 164 -92 23 -236 32 -322 20z m311 -160 c296 -92 472 -330 524 -713
             12 -82 15 -257 5 -257 -3 0 -36 5 -75 11 -126 19 -264 -15 -387 -98 l-67 -44
             -14 23 c-34 54 -190 197 -261 238 -140 81 -306 129 -514 145 l-89 8 6 91 c18
             315 238 558 558 615 82 15 233 5 314 -19z m1756 -852 c180 -130 293 -281 335
             -448 20 -80 15 -200 -13 -281 -57 -167 -233 -354 -414 -439 -98 -45 -180 -63
             -299 -63 -170 0 -309 35 -502 125 l-107 51 39 44 c106 120 158 294 131 438
             -13 67 -10 70 54 81 118 19 328 110 441 190 87 61 194 181 238 263 20 39 41
             71 45 71 4 0 28 -15 52 -32z m-1276 -253 c122 -32 222 -113 271 -220 98 -212
             18 -439 -191 -545 -66 -33 -74 -35 -174 -35 -98 0 -111 2 -171 31 -95 46 -153
             101 -197 192 -36 73 -38 80 -38 176 1 127 23 188 99 272 108 120 255 167 401
             129z m-625 -549 c0 -7 18 -49 39 -92 54 -108 139 -192 249 -246 64 -32 81 -45
             76 -57 -30 -66 -65 -191 -74 -266 -23 -184 22 -404 125 -603 l42 -82 -51 -29
             c-111 -63 -263 -98 -385 -87 -159 15 -299 82 -416 201 -132 135 -194 277 -202
             465 -6 133 8 201 62 315 70 147 215 300 401 424 107 71 134 83 134 57z"
                  />
                </g>
              </svg>
            </button>
          </div>
          <div class="other-buttons">
            <button onclick="jetcool()" class="other-button">
              <svg
                xmlns="http://www.w3.org/2000/svg"
                viewBox="0 0 16 16"
                width="2rem"
                height="2rem"
                fill="currentColor"
              >
                <path
                  d="M8 16a.5.5 0 0 1-.5-.5v-1.293l-.646.647a.5.5 0 0 1-.707-.708L7.5 12.793V8.866l-3.4 1.963-.496 1.85a.5.5 0 1 1-.966-.26l.237-.882-1.12.646a.5.5 0 0 1-.5-.866l1.12-.646-.884-.237a.5.5 0 1 1 .26-.966l1.848.495L7 8 3.6 6.037l-1.85.495a.5.5 0 0 1-.258-.966l.883-.237-1.12-.646a.5.5 0 1 1 .5-.866l1.12.646-.237-.883a.5.5 0 1 1 .966-.258l.495 1.849L7.5 7.134V3.207L6.147 1.854a.5.5 0 1 1 .707-.708l.646.647V.5a.5.5 0 1 1 1 0v1.293l.647-.647a.5.5 0 1 1 .707.708L8.5 3.207v3.927l3.4-1.963.496-1.85a.5.5 0 1 1 .966.26l-.236.882 1.12-.646a.5.5 0 0 1 .5.866l-1.12.646.883.237a.5.5 0 1 1-.26.966l-1.848-.495L9 8l3.4 1.963 1.849-.495a.5.5 0 0 1 .259.966l-.883.237 1.12.646a.5.5 0 0 1-.5.866l-1.12-.646.236.883a.5.5 0 1 1-.966.258l-.495-1.849-3.4-1.963v3.927l1.353 1.353a.5.5 0 0 1-.707.708l-.647-.647V15.5a.5.5 0 0 1-.5.5z"
                />
              </svg>
            </button>
            <button onclick="decrement()" class="temp-button">
              <svg
                xmlns="http://www.w3.org/2000/svg"
                fill="none"
                viewBox="0 0 24 24"
                stroke-width="2"
                stroke="currentColor"
                width="2rem"
                height="2rem"
              >
                <path
                  stroke-linecap="round"
                  stroke-linejoin="round"
                  d="M19.5 8.25l-7.5 7.5-7.5-7.5"
                />
              </svg>
            </button>
            <button
              class="other-button"
              onclick="(function() { window.location.href = baseURL + '#timer'})()"
            >
              <svg
                xmlns="http://www.w3.org/2000/svg"
                viewBox="0 0 256 256"
                width="2rem"
                height="2rem"
              >
                <circle
                  cx="128"
                  cy="128"
                  r="88"
                  fill="none"
                  stroke="currentColor"
                  stroke-linecap="round"
                  stroke-linejoin="round"
                  stroke-width="20"
                />
                <line
                  x1="128"
                  y1="128"
                  x2="167.6"
                  y2="88.4"
                  fill="none"
                  stroke="currentColor"
                  stroke-linecap="round"
                  stroke-linejoin="round"
                  stroke-width="20"
                />
                <line
                  x1="104"
                  y1="8"
                  x2="152"
                  y2="8"
                  fill="none"
                  stroke="currentColor"
                  stroke-linecap="round"
                  stroke-linejoin="round"
                  stroke-width="20"
                />
              </svg>
            </button>
          </div>
          <div id="timer" class="modal">
            <a href="#"></a>
            <div class="modal-content">
              <a href="#">X</a>
              <select name="timer" id="timer-value">
                <option value="0">1 hour</option>
                <option value="1">2 hours</option>
                <option value="2">3 hours</option>
                <option value="3">4 hours</option>
                <option value="4">4 hours 30 mins</option>
                <option value="5">5 hours</option>
                <option value="6">5 hours 30 mins</option>
                <option value="7">6 hours</option>
              </select>
              <button onclick="setTimer()">Set Timer</button>
              <button onclick="cancelTimer()">Cancel Timer</button>
            </div>
          </div>
        </div>
      </div>
    </main>

    <script>
      // const baseURL = "http://192.168.29.35";
      const baseURL = window.location.origin;
      const temp = document.querySelector(".temp");
      const timerValue = document.querySelector("#timer-value");
      const timerInfo = document.querySelector(".timer-info");

      const timerNames = ["1", "2", "3", "4", "4 30", "5", "5 30", "6"];

      window.addEventListener("offline", () => {
        toggleOffline(true);
      });

      window.addEventListener("online", () => {
        getData();
        toggleOffline();
      });

      document.addEventListener("visibilitychange", function () {
        if (!document.hidden) {
          getData();
        }
      });

      document.addEventListener("keydown", function (e) {
        switch (e.key) {
          case "ArrowUp":
            increment();
            break;
          case "ArrowDown":
            decrement();
            break;
          case "Enter":
            togglePower();
            break;
          case " ":
            jetcool();
            break;
          case "Shift":
            swing();
            break;
        }
      });

      async function timedFetch(url) {
        const res = await fetch(url, {
          signal: AbortSignal.timeout(500),
        }).catch((err) => {
          toggleOffline(true);
        });
        return res;
      }

      function getData() {
        timedFetch(`${baseURL}/data`)
          .then((res) => res.json())
          .then((data) => {
            console.log(data);
            temp.innerText = data.temp;
            if (data.power) document.body.classList.add("powerON");
            else document.body.classList.remove("powerON");
            if (data.timer !== "") {
              timerInfo.firstElementChild.innerText = data.timer;
              timerInfo.style.visibility = "visible";
            } else timerInfo.style.visibility = "hidden";
            toggleOffline();
          });
      }

      function togglePower() {
        timedFetch(`${baseURL}/power`)
          .then((res) => res.text())
          .then((data) => {
            if (data === "ON") document.body.classList.add("powerON");
            else document.body.classList.remove("powerON");
          });
      }

      function increment() {
        timedFetch(`${baseURL}/increment`)
          .then((res) => res.text())
          .then((data) => {
            if (data) temp.innerText = data;
          });
      }

      function decrement() {
        timedFetch(`${baseURL}/decrement`)
          .then((res) => res.text())
          .then((data) => {
            if (data) temp.innerText = data;
          });
      }

      function swing() {
        timedFetch(`${baseURL}/swing`)
          .then((res) => res.text())
          .then((data) => {
            console.log(data);
          });
      }

      function jetcool() {
        timedFetch(`${baseURL}/jetcool`)
          .then((res) => res.text())
          .then((data) => {
            temp.innerText = data;
          });
      }

      function fan() {
        timedFetch(`${baseURL}/fan`)
          .then((res) => res.text())
          .then((data) => {
            temp.innerText = data;
          });
      }

      function setTimer() {
        window.location = baseURL + "#";
        const time = calculateTimeforDate(timerValue.value);
        timedFetch(`${baseURL}/setTimer?value=${timerValue.value}&time=${time}`)
          .then((res) => res.text())
          .then((data) => {
            timerInfo.firstElementChild.innerText = data;
            timerInfo.style.visibility = "visible";
          });
      }

      function cancelTimer() {
        window.location = baseURL + "#";
        timedFetch(`${baseURL}/cancelTimer`)
          .then((res) => res.text())
          .then((data) => {
            timerInfo.style.visibility = "hidden";
            timerInfo.firstElementChild.innerText = "0";
          });
      }

      function toggleOffline(isOffline = false) {
        const container = document.querySelector(".container");
        const div = document.querySelector(".offline");

        if (isOffline) {
          container.style.display = "none";
          div.style.display = "flex";
          document.body.classList.remove("powerON");
        } else {
          div.style.display = "none";
          container.style.display = "flex";
        }
      }

      function calculateTimeforDate(index) {
        let [hour, min] = timerNames[index].split(" ").map((i) => Number(i));
        min = min ?? 0;
        let currentTime = new Date().getTime();
        let updatedTime = new Date(
          currentTime + hour * 60 * 60000 + min * 60000
        );

        return updatedTime.toLocaleString([], {
          hour: "2-digit",
          minute: "2-digit",
        });
      }
    </script>
  </body>
</html>




)====="; 
