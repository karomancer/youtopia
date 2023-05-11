import React, { useState, useEffect } from "react";
import { collection, onSnapshot } from "firebase/firestore";

import { db } from "./firebase.js";
import "./App.css";
import CityPieChart from "./components/CityPieChart.js";
import BluetoothContainer from "./BluetoothContainer.js";

function App() {
  const [cityData, setCityData] = useState(null);
  useEffect(() => {
    onSnapshot(collection(db, "city_data"), (snapshot) => {
      setCityData(snapshot.docs[0]?.data());
      // console.log(snapshot.docs.map(doc => doc.data()))
    });
  }, []);
  return (
    <div className="App">
      <BluetoothContainer>
        <h2> TODO List App</h2>
        <CityPieChart collection={cityData} />
      </BluetoothContainer>
    </div>
  );
}
export default App;
