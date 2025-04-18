import { useState, useEffect } from 'react';
import Constants from '../constents.js';
import HighScoreCard from './highScoreCard.js';
import styles from '../styles/highScores.module.css'
import LoadingBar from './loadingData.js';
import { useSocket } from './socketContext.js'


const HighScores = () => { 
  const [highScores, setHighScores] = useState([]); // Initialize as an array
  const [loading, setLoading] = useState(true); // Track loading state
  const [error, setError] = useState(null); // Track error state
  const socket = useSocket();
    useEffect(() => {
        socket.emit('getHighScore');
      
          // Listen for the login response from the server
          socket.on('getHighScoreResponse', (response) => {
            if (response.status === Constants.WORK_STATUS) {
              setHighScores(JSON.parse(response.statistics));
              setLoading(false);
            } else {
              console.log("response: " + response);
              setLoading(false);
              setError("Failed to load high scores");
              setLoading(false);
            }
          });

          return () => {
            socket.off('getHighScoreResponse');
        };
      }, []);

      if (loading) return <LoadingBar />;
      if (error) return <p>{error}</p>;

      return (
          <div>
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

export default HighScores 