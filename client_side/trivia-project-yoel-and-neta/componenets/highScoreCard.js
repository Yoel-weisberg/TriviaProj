// UserCard.js
import React from 'react';
import styles from '../styles/highScoreCard.module.css';  // Importing our CSS module

const HighScoreCard = ({ userName, userScore }) => {
    return (
        <div className={styles.card}>
            <h2 className={styles.name}>{userName}</h2>
            <p className={styles.score}>Score: {userScore}</p>
        </div>
    );
}

export default HighScoreCard;