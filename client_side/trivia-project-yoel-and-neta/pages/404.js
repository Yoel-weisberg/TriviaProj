// pages/404.js
import Image from 'next/image';
import Link from 'next/link';
import styles from '../styles/404.module.css'; // You should create this CSS module for styling

const Custom404 = () => {
    return (
      <div className={styles.errorPage}>
        <h1 className={styles.title}>Oops!</h1>
        <h2 className={styles.subtitle}>It looks like this page is a mystery...</h2>
        <Image
          src="/404.jpg" // Change this path to where your image is stored
          alt="Puzzled detective"
          width={500}
          height={500}
        />
        <p className={styles.description}>But don't worry, you can click below to go back to the fun!</p>
        <Link href="/">
          <p className={styles.backButton}>Go Back to Home</p>
        </Link>
      </div>
    );
  }
  
  export default Custom404;
