const ExtractTextPlugin = require("extract-text-webpack-plugin");
const globImporter = require('node-sass-glob-importer');

const extractSASS = new ExtractTextPlugin({
    filename: 'styles.css',
});

module.exports = {
    entry: [
        './src/Main.scss',
        './lib/js/src/main.js'
    ],
    output: {
        path: __dirname + '/public',
        filename: 'bundle.js',
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
                        // {
                        //     loader: 'postcss-loader'
                        // },
                        {
                            loader: 'sass-loader',
                            options: {
                                importer: globImporter()
                            }
                        }
                    ]
                })
            }
        ]
    },
    plugins: [
        extractSASS,
    ]
};
