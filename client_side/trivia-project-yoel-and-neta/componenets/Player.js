import { useState } from 'react';
import styles from '../styles/Player.module.css'

function Player({ name }) {
    return (
        <div className={styles.playerCard}>
            <p className={styles.playerName}>{name}</p>
        </div>
    );
}

export default Player;
