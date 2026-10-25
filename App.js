import React from "react";

function Student(props) {
  return (
    <div>
      <h2>Name: {props.name}</h2>
      <h3>Course: {props.course}</h3>
    </div>
  );
}

function App() {
  return (
    <div>
      <h1>React Props Example</h1>

      <Student name="Drishti" course="BTech CSE" />
      <Student name="Rahul" course="Cyber Security" />
    </div>
  );
}

export default App;