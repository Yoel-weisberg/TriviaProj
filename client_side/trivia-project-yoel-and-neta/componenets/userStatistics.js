import { useState, useEffect } from 'react';
import { IoStatsChart } from 'react-icons/io';
import { MdHighScore } from 'react-icons/md';
import { FaRegClock, FaGamepad, FaQuestionCircle } from 'react-icons/fa';
import { PieChart, Pie, Cell, Tooltip } from 'recharts';
import CountUp from 'react-countup';
import Constants from '../constents.js';
import styles from '../styles/userStatistics.module.css'
import LoadingBar from './loadingData.js';
import { useSocket } from './socketContext.js'

const UserStats = () => { 
  const [userStats, setUserStats] = useState([]); // Initialize as an array
  const [loading, setLoading] = useState(true); // Track loading state
  const [error, setError] = useState(null); // Track error state
  const socket = useSocket();
    useEffect(() => {
        socket.emit('getPersonalStats');
      
          // Listen for the login response from the server
          socket.on('getPersonalStatsResponse', (response) => {
            if (response.status === Constants.WORK_STATUS) {
              setUserStats(JSON.parse(response.statistics));
              setLoading(false);
            } else {
              setLoading(false);
              setError("Failed to load user stats");
              setLoading(false);
            }
          });

          return () => {
            socket.off('getPersonalStatsResponse');
        };
      }, []);

      if (loading) return <LoadingBar />;
      if (error) return <p>{error}</p>;

      const dataPie = [
        { name: "Right Answers", value: userStats.right_ans || 0 },
        { name: "Wrong Answers", value: (userStats.total_ans - userStats.right_ans) || 0 }
      ];
    
      const COLORS = ['#0088FE', '#FF8042'];
    
      return (
        <div className={styles.statsContainer}>
          <div className={styles.statItem}>
            <IoStatsChart />
            <p>User ID: {userStats.user_id}</p>
          </div>
          <div className={styles.statItem}>
            <FaQuestionCircle />
            <p>Total Answers: <CountUp end={userStats.total_ans || 0} duration={2.5} /></p>
          </div>
          <div className={styles.statItem}>
            <FaRegClock />
            <p>Avg Answer Time: <CountUp end={userStats.avg_ans_time || 0} duration={2.5} decimals={2} /> seconds</p>
          </div>
          <div className={styles.statItem}>
            <FaGamepad />
            <p>Games Played: <CountUp end={userStats.games_played || 0} duration={2.5} /></p>
          </div>
          <div className={styles.statItem}>
            <MdHighScore />
            <p>High Score: <CountUp end={userStats.highScore || 0} duration={2.5} /></p>
          </div>
          <div className={styles.statItem}>
            <PieChart width={200} height={200}>
              <Pie data={dataPie} cx={100} cy={100} outerRadius={80} fill="#8884d8" dataKey="value" label>
                {
                  dataPie.map((entry, index) => <Cell key={`cell-${index}`} fill={COLORS[index % COLORS.length]} />)
                }
              </Pie>
              <Tooltip />
            </PieChart>
          </div>
        </div>
      );
}

export default UserStats