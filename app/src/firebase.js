import { initializeApp } from "firebase/app";
import { getFirestore } from 'firebase/firestore';
import firebaseConfig from "./firebase.config"

const firebaseApp = initializeApp(firebaseConfig);
const db = getFirestore(firebaseApp);
export { db }