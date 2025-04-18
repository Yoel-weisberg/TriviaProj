import Image from 'next/image';
import styles from '../styles/Menu.module.css'
import NavbarButton from '../componenets/menuButton';
const Navbar = () => {
  return (
    <>
      <div className={styles.logoImage}>
        <Image
          src='/logo.jpg' // Adjust the path based on where you saved it
          alt="Brain Buzzer Logo"
          layout="fixed"
          width={250}
          height={250}
        />
      </div>

      <>
        <nav className={styles.navbar}>

          <NavbarButton
            name="CreateRoom"
          />

          <NavbarButton
            name="JoinRoom"
          />

          <NavbarButton
            name="statistics"
          />

          <NavbarButton
            name="logout"
          />
          
        </nav>
      </>
    </>
  );
};

export default Navbar;
