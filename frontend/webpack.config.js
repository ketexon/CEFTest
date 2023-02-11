const HtmlWebpackPlugin = require('html-webpack-plugin');
const path = require('path');

module.exports = {
  mode: 'development',
  entry: './src/index.tsx',
  module: {
    rules: [
      {
        test: /\.tsx?$/,
        use: 'ts-loader',
        exclude: /node_modules/,
      },
    ],
  },
  watchOptions: {
    ignored: ['**/node_modules']
  },
  resolve: {
    extensions: ['.tsx', '.ts', '.js'],
  },
  output: {
    filename: 'App.js',
    path: path.resolve(__dirname, '../assets/App'),
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: "static/index.html"
    })
  ]
};