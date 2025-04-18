import React from 'react';
import ReactLoading from 'react-loading';
import styles from '../styles/loadingData.module.css'
const LoadingBar = () => {
    return (
            <div className={styles.containerStyle}>
                <ReactLoading type="cylon" color="#000" height={200} width={200} className={styles.reactloading}/>
                <p>Loading data...</p>
            </div>
    );
};

export default LoadingBar;
