import { useState, useRef } from "react";
import './terminal.css'
import axios from "axios";
export default function Terminal() {
    const [history, setHistory] = useState([
        "Microsoft Windows [Version 10.0.26100.1]",
        "(c) Microsoft Corporation. All rights reserved.",
        "",
        "Type 'help' and press Enter.",
        ""
    ]);

    const [command, setCommand] = useState("");
    const fileInput = useRef(null);

    const handleUpload = async(e) => {
        const file = e.target.files[0];

        if (!file) return;

        if (!file.name.toLowerCase().endsWith(".csv")) {
            setHistory(prev => [
                ...prev,
                `Rejected: ${file.name}`,
                "Upload failed: Please choose a .csv file."
            ]);
            e.target.value = "";
            return;
        }

        setHistory(prev => [
            ...prev,
            `Loaded: ${file.name}`,
            "Uploading dataset...",
            "Waiting for backend..."
        ]);
        const formdata=new FormData();

        formdata.append("file",file);

        try {
                const response = await axios.post("http://localhost:8000/predict", formdata, {
                    responseType: "blob",
                });

                const url = window.URL.createObjectURL(response.data);

                const link = document.createElement("a");
                link.href = url;
                link.download = "decision_tree_report.csv";
                document.body.appendChild(link);
                link.click();
                link.remove();

                window.URL.revokeObjectURL(url);

                setHistory(prev => [
                    ...prev,
                    "Backend processing complete.",
                    "Decision tree report downloaded successfully."
                ]);
            }
            catch (err) {
                console.error(err);

                const message = err.response?.data?.detail ?? err.message;

                setHistory(prev => [
                    ...prev,
                    `Upload failed: ${message}`
                ]);
            }
        
    };

    const handleCommand = (e) => {
        if (e.key !== "Enter") return;

        const cmd = command.trim().toLowerCase();

        setHistory(prev => [
            ...prev,
            `C:\\UserYou\\DecisionTree> ${cmd}`
        ]);
        
        if(cmd== "help")
        {
            setHistory(prev => [
                ...prev,
                `use the command 'upload' to upload your csv file and wait for the magic to happen......:)
                Apart from that try using hello,what etc to see which command works well`
               
                
            ]);
        }

        else if(cmd=="hello")
        {
            setHistory(prev => [
                ...prev,
                `Hello there stranger, i hope you are doing well ! `
            ]);
        }

        else if(cmd=="what")
        {
            setHistory(prev => [
                ...prev,
                `What are you cooking there? `
            ]);

        }
        else if (cmd === "upload") {
            fileInput.current.click();
        } else if (cmd === "clear") {
            setHistory([]);
        } else {
            setHistory(prev => [
                ...prev,
                `Unknown command: ${cmd}`
            ]);
        }

        setCommand("");
    };

    return (
        <div className="terminal-window">
            <input
                ref={fileInput}
                type="file"
                hidden
                accept=".csv"
                onChange={handleUpload}
            />

            {history.map((line, i) => (
                <div key={i}>{line}</div>
            ))}
            <br/>
            <div className="prompt">
                <span>C:\UserYou\DecisionTree&gt; </span>

                <input
                    value={command}
                    onChange={(e) => setCommand(e.target.value)}
                    onKeyDown={handleCommand}
                    autoFocus
                />
            </div>
        </div>
    );
}
