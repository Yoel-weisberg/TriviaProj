import Image from 'next/image';
import styles from '../styles/Logout.module.css';  
import { useEffect, useState } from 'react';
import { useSocket } from '../componenets/socketContext';

function Logout() {
    const [logginOut, setlogginOut] = useState(true);
    const socket = useSocket();
    useEffect(() => {
        socket.emit('logout');
        socket.on('logoutResponse', (response) => {
            if (response.status === Constants.WORK_STATUS) {
                setlogginOut(false);
            } else {
                alert('error while reiving from server, try again later');
            }
        });
    });

    if(logginOut) return <p>Logging you out...</p>

    return (
        <div className={styles.container}>
            <div className={styles.messageBox}>
                <h1>You've successfully logged out!</h1>
                <p>Thanks for playing. We hope to see you again soon!</p>
            </div>
            <div className={styles.imageBox}>
                {/* Assuming you have an image named 'trivia-logout.jpg' in your public folder */}
                <Image src="/logout.png" alt="Trivia Game" width={500} height={300} />
            </div>
        </div>
    );
}

export default Logout;
