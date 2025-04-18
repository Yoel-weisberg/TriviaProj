import styles from '../styles/menyButton.module.css'
import Link from 'next/link';
import { useState, useEffect } from 'react';
import { TbLogout2 } from "react-icons/tb";
import { FaPlus } from "react-icons/fa";
import { FcStatistics } from "react-icons/fc";
import { AiOutlineEnter } from "react-icons/ai";


const NavbarButton = (props) => {
  let Component;

  // Dynamically import the icon component
  switch (props.name) {
    case "CreateRoom":
      Component = FaPlus;
      break;
    case "JoinRoom":
      Component = AiOutlineEnter;
      break;
    case "statistics":
      Component = FcStatistics;
      break;
    case "logout":
      Component = TbLogout2;
      break;

    default:
      Component = TbLogout2;
      break;
  }

  return (
    <Link href={`/${props.name}`} passHref className={styles.navbarItem}>
      {Component ? <Component /> : <p>No component matched!</p>}
      <div className={styles.navbarItemText}>
        <h1>{props.name}</h1>
      </div>
    </Link>
  );
}
export default NavbarButton;