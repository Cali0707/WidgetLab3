import {CartesianGrid, LineChart, ResponsiveContainer, XAxis, Line, YAxis, Tooltip, Legend} from "recharts";

interface TimeSeriesData {
    timestamp: Date,
    photoResistorValue: number,
    thermistorValue: number
}

interface LineGraphProps {
    data: TimeSeriesData[]
}

const LineGraph = ({data}: LineGraphProps) => {
    // Filter total data set to specific type to display
    // const filteredData = data.filter(d => types.includes(d.type));
    // console.table(filteredData)
    // Make line for each type provided
    // const lines = types.map(t => <Line type={"monotone"} dataKey={t} />)
    // console.table(lines)

    return (
        <ResponsiveContainer width={"80%"} height={250}>
            <LineChart height={200} data={data}>
                <CartesianGrid strokeDasharray={"3 3"}/>
                <XAxis dataKey={"timestamp"} />
                <YAxis />
                <Tooltip />
                <Legend />
                <Line type={"monotone"} dataKey={"thermistorValue"} stroke="#8884d8"/>
                <Line type={"monotone"} dataKey={"photoResistorValue"} stroke={"#82ca9d"}/>
            </LineChart>
        </ResponsiveContainer>
    )
}

export default LineGraph;
