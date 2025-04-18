// _app.js
import React from 'react';
import { SocketProvider } from '../componenets/socketContext';

function TriviaApp({ Component, pageProps }) {
  return (
    <SocketProvider>
      <Component {...pageProps} />
    </SocketProvider>
  );
}

export default TriviaApp;