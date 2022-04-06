<template>
  <component :is="`${screen}Screen`" />
</template>

<script>
import LoadingScreen from './components/LoadingScreen.vue'

export default {
  name: 'App',
  components: {
    LoadingScreen
  },

  data() {
    return {
      screen: 'Loading'
    }
  },

  methods: {
    setScreen(screen) {
      this.screen = screen
    }
  }
}
</script>

<style>
* {
  margin: 0;
  padding: 0;
  border: 0;
  outline: none;
}

body {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  background: #1a252e;
  color: white;
  overflow: hidden;
}
</style>
