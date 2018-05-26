const webpackConfig = require('./webpack.config');

module.exports = {
  ...webpackConfig,

  bail: false,
  devtool: 'eval',
  mode: 'development',
  watch: true
};
