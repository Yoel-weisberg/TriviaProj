import { useRouter } from 'next/router';
import { useEffect, useState } from 'react';
import { useSocket } from '../../components/socketContext';  // Ensure the path is correct
import Player from '../../componenets/Player';

export default function Room() {
    const router = useRouter();
    const { roomId } = router.query;
    const [players, setPlayers] = useState([]);
    const socket = useSocket();

    useEffect(() => {
        if (!socket) return;

        socket.emit('getPlayersInRoom', { roomId });

        socket.on('getPlayersInRoomResponse', (response) => {
            if (response.status === 'WORK_STATUS') { // Ensure you have a constant or correct status check
                setPlayers(response.players);
            } else {
                alert('Something went wrong');
            }
        });

        // Cleanup the effect
        return () => {
            socket.off('getPlayersInRoomResponse');
        };
    }, [socket, roomId]);

    return (
        <div>
            <h1>Room: {roomId}</h1>
            <ul>
                {players.map((player, index) => (
                    <Player key={index} name={player} />
                ))}
            </ul>
        </div>
    );
}
