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
            <LineGraph data={graphData} />
        </div>
  );
}

export default App;
