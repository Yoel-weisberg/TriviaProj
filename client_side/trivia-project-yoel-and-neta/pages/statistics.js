import UserStats from "../componenets/userStatistics";
import HighScores from "../componenets/highScores";
import styles from '../styles/statistics.module.css';


const Statistics = () => { 
    return (
        <div className={styles.container}>
            <UserStats />
            <HighScores />
        </div>
    );
}

export default Statistics;