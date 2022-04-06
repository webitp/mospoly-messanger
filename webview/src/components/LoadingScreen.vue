<template>
  <div class="loading-screen">
    <div class="loading-screen__container">
      <h1>
        <span>Mospoly</span>
        Messanger
      </h1>
      <p>Loading{{dotes}}</p>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      dotes: ''
    }
  },

  mounted() {
    setInterval(() => {
      if (this.dotes.length < 3)
        this.dotes += '.'
      else
        this.dotes = ''
    }, 500)
  }
}
</script>

<style lang="scss" scoped>
.loading-screen {
  width: 100vw;
  height: 100vh;
  display: flex;
  justify-content: center;
  align-items: center;
  user-select: none;

  h1 {
    font-size: 10vh;
    animation: loading 3s ease-in-out infinite;

    span {
      color: #00b3ff;
    }
  }

  p {
    margin-top: 3vh;
    font-size: 4vh;
  }
}

@keyframes loading {
  from, to {
    transform: scale(1);
  }

  50% {
    transform: scale(1.025);
  }
}
</style>