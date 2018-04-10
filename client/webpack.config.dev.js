const webpackConfig = require('./webpack.config');

module.exports = {
  ...webpackConfig,

  bail: false,
  devtool: 'eval',
  mode: 'development',
  devServer: {
    contentBase: './public',
    historyApiFallback: true,
    inline: true,
    port: 3000,
    stats: 'errors-only',
  },
};
