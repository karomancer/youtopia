const LOCAL_NAME = "Youtopia";
const SERVICE_UUID = "2d32cb10-dd61-11ed-b5ea-0242ac120002";

let infra = "e9985dc9-f6c5-44ab-83b8-1dcd02b9c01b";
let utopiaIsCreated = false;

function createYoutopia() {
  const youTopia = new Youtopia();
}

class Youtopia {
  constructor() {
    this.device = null;
    this.port = null;
    this.writer = null;

    this.characteristics = {}; // descriptor name => characteristic
    this.characteristicValues = {}; // descriptor name => count
    this.chartData = [];

    this.setupConnections();
  }

  async setupConnections() {
    // await this.connectToSerial();
    await this.connectToBluetooth();
  }

  async connectToSerial() {
    this.port = await navigator.serial?.requestPort();
    await this.port.open({ baudRate: 9600 });

    this.writer = this.port.writable.getWriter();
  }

  async connectToBluetooth() {
    console.log("Seeking a better place to live...");

    this.device = await navigator.bluetooth
      .requestDevice({
        filters: [
          {
            name: LOCAL_NAME,
            services: [SERVICE_UUID],
          },
        ],
      })
      .then((device) => {
        console.log(`Welcome to ${LOCAL_NAME}!`);
        return device.gatt.connect();
      })
      .then(async (server) => {
        console.log("Got cell service!");
        return server.getPrimaryService(SERVICE_UUID);
      })
      .catch((error) => {
        console.error(error);
      });
    
    this.populateAllCharacteristics();
  }

  async populateAllCharacteristics() {
    const characteristicList = await this.device.getCharacteristics();

    characteristicList.forEach(async (characteristic) => {
      const name = await this.getCharacteristicDescriptor(characteristic);
      this.characteristics[name] = characteristic;
      this.characteristicValues[name] = 0; // @TODO use database

      characteristic.startNotifications().then((c, i) => {
        c.addEventListener(
          "characteristicvaluechanged",
          this.handleCharacteristicValueChanged(name, i)
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

      // const dataArrayBuffer = this.encoder.encode({ [name]: value });
      // await this.writer.write(dataArrayBuffer);
    };
  }

  drawChart() {
    var svg = d3.select("svg"),
      width = svg.attr("width"),
      height = svg.attr("height"),
      radius = Math.min(width, height) / 2,
      g = svg
        .append("g")
        .attr("transform", "translate(" + width / 2 + "," + height / 2 + ")");

    var color = d3.scaleOrdinal([
      "#4daf4a",
      "#377eb8",
      "#ff7f00",
      "#984ea3",
      "#e41a1c",
    ]);

    // Generate the pie
    var pie = d3.pie();

    // Generate the arcs
    var arc = d3.arc().innerRadius(0).outerRadius(radius);

    //Generate groups
    var arcs = g
      .selectAll("arc")
      .data(pie(this.chartData))
      .enter()
      .append("g")
      .attr("class", "arc");

    //Draw arc paths
    arcs
      .append("path")
      .attr("fill", function (d, i) {
        return color(i);
      })
      .attr("d", arc);
  }
}
