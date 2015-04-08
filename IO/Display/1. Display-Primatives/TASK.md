#Task

1. Display an image with three primative shapes : a red triangle, a blue square and a green circle.

Bonus - I'm guessing that possibly the most practicle route for live (ie real-time or animated) graphics display may well be a front end of Browser/Canvas/WebSockets with the backend language (eg Go / Haskell / Node / C) providing the live graphic instructions over the WebSocket. The motivation for this task is mainly to settle this hypothesis.

GUIdisplay. Build an HTML5 Canvas front end that accepts graphic instructions over websocket.
GUIBackend. Build a library that provides draw instructions to a backend language, so it can send to the GUI.

