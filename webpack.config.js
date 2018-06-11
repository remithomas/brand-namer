const ExtractTextPlugin = require("extract-text-webpack-plugin");
const globImporter = require('node-sass-glob-importer');

const extractSASS = new ExtractTextPlugin({
    filename: 'styles.css',
});

module.exports = {
    entry: [
        './src/Main.scss',
        './lib/js/src/Main.js',
        './node_modules/socket.io-client/dist/socket.io.js',
    ],
    output: {
        path: __dirname + '/public',
        filename: 'bundle.js',
    },
    node: {
      fs: 'empty'
    },
    module: {
        rules: [
            {
                test: /\.css$/,
                use: [{ loader: 'style-loader' }, { loader: 'css-loader' }],
            },
            { 
                test: /\.scss$/, 
                use: extractSASS.extract({
                    fallback: "style-loader",
                    use: [
                        {
                            loader: 'css-loader'
                        }, 
                        {
                            loader: 'postcss-loader'
                        },
                        {
                            loader: 'sass-loader',
                            options: {
                                importer: globImporter()
                            }
                        }
                    ]
                })
            },
            {
                test: /\.svg$/,
                loader: 'file-loader'
            }
        ]
    },
    plugins: [
        extractSASS,
    ]
};
