import React, { useState } from 'react';
import Constants from '../constents';
import { useRouter } from 'next/router';
import styles from '../styles/login.module.css'
import { useSocket } from '../componenets/socketContext';


const Login = () => {
  const router = useRouter();
  const [userName, setUserName] = useState('');
  const [password, setPassword] = useState('');
  const [passwordError, setPasswordError] = useState('');
  const socket = useSocket();
  
  const handleLogin = (e) => {
    e.preventDefault(); // Prevent the form from refreshing the page
    // Emit the login event to the server with username and password
    socket.emit('login', JSON.stringify({
      username : userName,
      password: password
    }));

    // Listen for the login response from the server
    socket.on('LoginResponse', (response) => {
      if (response.status === Constants.WORK_STATUS) {
        console.log('Login response');
        router.push('/Menu');
      } else {
        setPasswordError("Wrong password");
      }
    });

    return () => {
      socket.off('LoginResponse');
  };
  };


  return (
    <div className={styles.mainContainer}>
      <div className={styles.titleContainer}>
        <div>Login</div>
      </div>
      <br />
      <div className={styles.inputContainer}>
        <input
          value={userName}
          placeholder="Enter your user name here"
          onChange={(ev) => setUserName(ev.target.value)}
          className={styles.inputBox}
        />
      </div>
      <br />
      <div className={styles.inputContainer}>
        <input
          value={password}
          placeholder="Enter your password here"
          onChange={(ev) => setPassword(ev.target.value)}
          className={styles.inputBox}
        />
        <label className={styles.errorLabel}>{passwordError}</label>
      </div>
      <br />
      <div className={styles.inputContainer}>
        <input className={styles.inputButton} type="button" value="Login" onClick={handleLogin}/>
      </div>
    </div>
  );
};

export default Login;
