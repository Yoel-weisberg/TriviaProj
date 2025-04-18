import React, { createContext, useContext, useMemo } from 'react';
import io from 'socket.io-client';

// Create a new context for the socket
const SocketContext = createContext();

// Custom hook to access the socket instance
export const useSocket = () => useContext(SocketContext);
// Assuming your server is running on this URL
const SOCKET_URL = 'http://127.0.0.1:5000';


// Socket provider component
export const SocketProvider = ({ children }) => {
  const socket = useMemo(() => {
    console.log('Socket redefinition');
    return io(SOCKET_URL, {
    reconnection: true, // Enable reconnection
    reconnectionAttempts: 100, // Maximum number of reconnection attempts
    reconnectionDelay: 1000, // Delay between each reconnection attempt (in milliseconds)
    })
  }, []);
  return (
    <SocketContext.Provider value={socket}>
      {children}
    </SocketContext.Provider>
  );
};
