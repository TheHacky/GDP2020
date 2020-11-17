using System;
using UnityEngine;

namespace Code
{
    public class EnemySpawner : MonoBehaviour
    {
        [SerializeField] private Enemy _enemyPrefab = null;

        private void Start()
        {
            Instantiate(_enemyPrefab, transform.position, transform.rotation);
        }
    }
}