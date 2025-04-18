import React, { useState } from 'react';
import { useSocket } from '../componenets/socketContext';
import styles from '../styles/CreateRoom.module.css';

const CreateRoom = () => {
    const [roomName, setRoomName] = useState('');
    const [timePerQuestion, setTimePerQuestion] = useState('');
    const [maxPlayers, setMaxPlayers] = useState('');
    const [questionCount, setQuestionCount] = useState('');

    const socket = useSocket();

    const handleSubmit = (e) => {
        e.preventDefault(); // Prevent the form from refreshing the page
        // Emit the login event to the server with username and password
        socket.emit('createRoom', JSON.stringify({
          roomName : roomName,
          maxUsers: maxPlayers,
          answerTimeout: timePerQuestion,
          questionCount: questionCount
        }));
        console.log('data send');
        // Listen for the login response from the server
        socket.on('createRoomResponse', (response) => {
          if (response.status === Constants.WORK_STATUS) {
            console.log('Login response');
            router.push('/Menu');
          } else {
            alert('somthing went wrong');
          }
        }
    )
    return () => {
        socket.off('createRoomResponse');
    };
    }
    

    return (
        <div className={styles.container}>
            <form onSubmit={handleSubmit} className={styles.form}>
                <div>
                    <label htmlFor="roomName">Room Name:</label>
                    <input
                        id="roomName"
                        type="text"
                        value={roomName}
                        onChange={(e) => setRoomName(e.target.value)}
                        className={styles.input}
                    />
                </div>
                <div>
                    <label htmlFor="questionTime">Question Time (seconds):</label>
                    <input
                        id="questionTime"
                        type="number"
                        value={timePerQuestion}
                        onChange={(e) => setTimePerQuestion(e.target.value)}
                        className={styles.input}
                    />
                </div>
                <div>
                    <label htmlFor="maxPlayers">Max Players:</label>
                    <input
                        id="maxPlayers"
                        type="number"
                        value={maxPlayers}
                        onChange={(e) => setMaxPlayers(e.target.value)}
                        className={styles.input}
                    />
                </div>

                <div>
                    <label htmlFor="questionCount">Max Players:</label>
                    <input
                        id="QuestionCount"
                        type="number"
                        value={questionCount}
                        onChange={(e) => setQuestionCount(e.target.value)}
                        className={styles.input}
                    />
                </div>
                <button type="submit" className={styles.button}>Create Room</button>
            </form>
        </div>
    );
};

export default CreateRoom;
