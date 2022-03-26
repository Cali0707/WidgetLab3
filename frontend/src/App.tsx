import React from 'react';
import './App.css';
import LineGraph from "./components/LineGraph";

const graphData = [
    {timestamp: new Date(Date.now() - 200), photoResistorValue: 22, thermistorValue: 19},
    {timestamp: new Date(Date.now() - 150), photoResistorValue: 17, thermistorValue: 15},
    {timestamp: new Date(Date.now() - 100), photoResistorValue: 22, thermistorValue: 19},
    {timestamp: new Date(Date.now() - 50), photoResistorValue: 22, thermistorValue: 19},
    {timestamp: new Date(Date.now()), photoResistorValue: 22, thermistorValue: 19}
]

function App() {
  return (
    <div className="App">
      <LineGraph data={graphData} />
    </div>
  );
}

export default App;
