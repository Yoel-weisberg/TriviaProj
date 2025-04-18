import { useState, useEffect } from 'react';
import socket from '../socket.js';
import Constants from '../constents.js';
import HighScoreCard from './highScoreCard.js';
import styles from '../styles/highScores.module.css'

const HighScores = () => { 
    const [highScores, setHighScores] = useState({});
    useEffect(() => {
        socket.emit('getHighScore');
      
          // Listen for the login response from the server
          socket.on('getHighScoreResponse', (response) => {
            if (response.status === Constants.WORK_STATUS) {
              setHighScores(JSON.parse(response.statistics));
            } else {
            }
          });

          return () => {
            socket.off('getHighScoreResponse');
        };
      }, []);

      return (
          <div className={styles.container}>
              <h1 className={styles.title}>High Scores</h1>
              {highScores.length > 0 ? (
                  highScores.map((score, index) => (
                      <HighScoreCard key={index} userName={score.username} userScore={score.highestScore} />
                  ))
              ) : (
                  <p>No high scores available.</p>
              )}
          </div>
      );
}