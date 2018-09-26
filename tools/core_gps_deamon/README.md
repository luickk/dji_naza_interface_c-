GPS Deamon - a linux multiclient and multithreaded socket server in C++ to distribute GPS data
===============================================================================================

Description
-----------

The GPS deaomn uses BSD TCP sockets and libpthread to handle new connections. In the main loop, it keeps listening
for new connections, and when a new client arrives, a new thread is created, which sends the GPS data to the client.

The raw TCP Server is based on [multichat](https://github.com/rbaron/multichat), the websocket server is based on [websocketpp](https://github.com/zaphoyd/websocketpp) lib.

Dependencies
-----------

- websocketpp (https://github.com/zaphoyd/websocketpp)
