# Brand namer... [![CircleCI](https://circleci.com/gh/remithomas/brand-namer.svg?style=svg)](https://circleci.com/gh/remithomas/brand-namer)

**Brand namer** because brand name availability it's so complicated 😭

> Currently in WIP

The project is simply: type your _term_, and the system gives you the availabled names (or their synonymes) in some languages for the domain `.com` and `Facebook`

- This project is/will be coded with love in [ReasonMl](http://reasonml.github.io/)
  - Backend: ExpressJs with [bs-express](https://github.com/reasonml-community/bs-express)
  - Frontend: ReactJs on [ReasonReact](https://reasonml.github.io/reason-react/)

## Requirements

* bs-platform `2.2.3`
* node `8.*`

## Back-end

### Installation

```bash
yarn install
```

### Development

BSB Development
```bash
yarn start
```

test
```bash
yarn test
```

Node Development
```bash
yarn run nodemon
```

Open [http://127.0.0.1:3001/api/namer](http://127.0.0.1:3001/api/namer) file in your browser.

## Front-end

### Installation

```bash
npm install
```

### Development

BSB Development
```bash
npm start:dev
```

Webpack Development
```bash
npm run build
```

Open [index.html](client/public/index.html) file in your browser.

## Todos (Stories)

- [X] Front-end setup
- [X] Back-end setup
- [X] Send request to API
- [ ] Show translations
- [ ] Api ask if domain exists


## Thanks

* Many thanks to [@Glennsl](https://github.com/glennsl) with his awesome lib [bs-json](https://github.com/glennsl/bs-json)
