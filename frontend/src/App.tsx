import React, {useEffect, useState} from 'react';
import './App.css';
import LineGraph, {TimeSeriesData} from "./components/LineGraph";

function App() {
    const defaultGraphData: TimeSeriesData[] = []
    const [graphData, setGraphData] = useState(defaultGraphData);
    useEffect(() => {
        fetch("/sensors/data")
            .then(result => result.json())
            .then(result => {
                console.table(result.waterDataPoints)
                setGraphData(result.waterDataPoints)
            })
    }, [])
    return (
        <div className="App">
            <div className="header">
                <h1>Water Quality Data</h1>
            </div>
            <div className="graph">
                <LineGraph data={graphData} />
            </div>
            <div className="explanation">
                <h3>Data Interpretation</h3>
                <p>The photoresistor produces light intensity measurements, which can be used as a proxy for turbidity. Light intensity values below the threshold suggests that there is high water turbidity and it may not be safe for drinking.</p>
                <p>Thermistors measure the water temperature. Temperatures above the threshold value are more likely to have pathogenic bacteria and may not be safe to drink.</p>
            </div>
        </div>
  );
}

export default App;
