import React from 'react';
import { FaUsers, FaRegQuestionCircle, FaClock, FaToggleOn, FaToggleOff } from 'react-icons/fa';
import { useSocket } from './socketContext';
import styles from '../styles/RoomCard.module.css';

const RoomCard = ({ roomId, roomName, maxPlayers, numOfQuestionsInGame, timePerQuestion, isActive }) => {
    const socket = useSocket();
    
    const handleClick = () => {
        socket.emit('joinRoom', JSON.stringify(roomId));

        // Listen for the login response from the server
        socket.on('joinRoomResponse', (response) => {
            if (response.status === Constants.WORK_STATUS) {
                router.push({
                    pathname: '/rooms/[roomsId]',
                    query: {roomId}
                });
            } else {
                alert('somthing went wrong');
            }
        });

        return () => {
            socket.off('joinRoomResponse');
        }
    }

    return (
        <div className={styles.card} onClick={handleClick}>
            <div className={styles.header}>
                <h2>{roomName}</h2>
                <div className={styles.status}>
                    {isActive ? <FaToggleOn className={styles.activeIcon} /> : <FaToggleOff className={styles.inactiveIcon} />}
                    {isActive ? 'Active' : 'Inactive'}
                </div>
            </div>
            <div className={styles.info}>
                <div className={styles.infoItem}>
                    <FaUsers />
                    <span>{maxPlayers} players</span>
                </div>
                <div className={styles.infoItem}>
                    <FaRegQuestionCircle />
                    <span>{numOfQuestionsInGame} questions</span>
                </div>
                <div className={styles.infoItem}>
                    <FaClock />
                    <span>{timePerQuestion} sec/question</span>
                </div>
            </div>
        </div>
    );
};

export default RoomCard;
