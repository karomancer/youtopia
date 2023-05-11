import React from "react"

import { debounce } from "./utils";

const SERVICE_NAME = "Youtopia"
const SERVICE_UUID = "2d32cb10-dd61-11ed-b5ea-0242ac120002";

class BluetoothContainer extends React.Component {
  sensingDevice = null;
  projectionDevice = null;
  port = null;
  encoder = new TextEncoder();
  characteristics = {}; // descriptor name => characteristic
  characteristicValues = {}; // descriptor name => count

    constructor() {
      super();

      this.state = {
        data: []
      }
    }

    async connectToDevice() {
      console.log("Looking for the city...");
      this.sensingDevice = await navigator.bluetooth
        .requestDevice({
          filters: [
            {
              name: SERVICE_NAME,
              services: ["996b65f2-61ff-43c5-9fd4-98144ff9fd8f"],
            },
          ],
        })
        .then((device) => {
          console.log(`Connected to city blocks`);
          return device.gatt.connect();
        })
        .then(async (server) => {
          console.log("Got city blocks service!");
          return server.getPrimaryService(SERVICE_UUID);
        })
        .catch((error) => {
          console.error(error);
        });
  
      this.populateAllCharacteristics();
    }
  
    async setupConnections() {
      await this.connectToDevice();
      console.log(`Welcome to Youtopia!`);
  
      const button = document.querySelector("#connect_btn");
      button.style.opacity = 0;
  
      setTimeout(() => {
        button.style.display = "none";
      }, 400);
    }
  
    async populateAllCharacteristics() {
      const characteristicList = await this.sensingDevice.getCharacteristics();
  
      characteristicList.forEach(async (characteristic) => {
        const name = await this.getCharacteristicDescriptor(characteristic);
        this.characteristics[name] = characteristic;
        this.characteristicValues[name] = 0; // @TODO use database
  
        characteristic.startNotifications().then((c, i) => {
          c.addEventListener(
            "characteristicvaluechanged",
            debounce((e) => this.handleCharacteristicValueChanged(name, i)(e))
          );
        });
      });
  
      this.chartData = Object.keys(this.characteristicValues).map((c) => 0);
      this.drawChart();
    }
  
    async getCharacteristicDescriptor(characteristic) {
      return await characteristic
        .getDescriptor("gatt.characteristic_user_description")
        .then((descriptor) => descriptor.readValue())
        .then((value) => new TextDecoder("utf-8").decode(value));
    }
  
    handleCharacteristicValueChanged(name, index) {
      return async (event) => {
        const value = event.target.value;
        this.characteristicValues[name]++;
  
        this.chartData = Object.values(this.characteristicValues);
  
        this.drawChart(this.chartData);
  
        console.log(`${name}: ${this.characteristicValues[name]}`);
      };
    }

    render() {
        return <>
            <button onClick={this.setupConnections.bind(this)}>Connect to Bluetooth</button>
        </>
    }
}

export default BluetoothContainer