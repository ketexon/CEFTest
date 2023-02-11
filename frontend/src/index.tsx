import * as React from "react";
import * as ReactDOM from "react-dom/client";

import {
	RouterProvider,
	createMemoryRouter
} from "react-router-dom";

import Home from "./Home"

const router = createMemoryRouter(
	[{
		path: "/",
		element: <Home/>
	}],
	{
		initialEntries: ["/"],
		initialIndex: 0
	}
)

const root = ReactDOM.createRoot(document.getElementById("root"));
root.render(
	<h1>Hello world!</h1>
);