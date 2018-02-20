const ExtractTextPlugin = require("extract-text-webpack-plugin");

const extractSASS = new ExtractTextPlugin({
    filename: 'styles.css',
});

module.exports = {
    entry: ['./src/BrandNamerApp.scss', './lib/js/src/main.js'],
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
                    use: ['css-loader', 'postcss-loader', 'sass-loader']
                })
            }
        ]
    },
    plugins: [
        extractSASS,
    ]
};
